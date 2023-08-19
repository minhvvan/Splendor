// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamTestGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SG_PlayerProfile.h"
#include "HUDMainMenu.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


USteamTestGameInstance::USteamTestGameInstance(): OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
												, OnFindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
{
	ConstructorHelpers::FClassFinder<UUserWidget> MAIN(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_MainMenu.WBP_MainMenu_C'"));
	if (MAIN.Succeeded())
	{
		MainMenuClass = MAIN.Class;
	}	
	
	ConstructorHelpers::FClassFinder<UUserWidget> MULT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_MultMenu.WBP_MultMenu_C'"));
	if (MULT.Succeeded())
	{
		MultMenuClass = MULT.Class;
	}

	PlayerInfo = new FPlayerProfile();
}

void USteamTestGameInstance::ShowMainMenu()
{
	if (!WidgetMainMenu)
	{
		WidgetMainMenu = CreateWidget(GetWorld(), MainMenuClass);
	}

	if (UGameplayStatics::DoesSaveGameExist(PlayerProfileSlot, 0))
	{
		LoadGame();
	}


	//UGameplayStatics::DeleteGameInSlot(PlayerProfileSlot, 0);
	
	WidgetMainMenu->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void USteamTestGameInstance::ShowMultMenu()
{
	if (!WidgetMultMenu)
	{
		WidgetMultMenu = CreateWidget(GetWorld(), MultMenuClass);
	}

	WidgetMultMenu->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void USteamTestGameInstance::StartSoloGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(PlayerProfileSlot, 0))
	{
		SaveGame();
	}

	UGameplayStatics::OpenLevel(this, FName("ThirdPersonMap"));
}

void USteamTestGameInstance::LoadGame()
{
	auto LoadGameInstance = Cast<USG_PlayerProfile>(UGameplayStatics::LoadGameFromSlot(PlayerProfileSlot, 0));

	if (LoadGameInstance)
	{
		LoadGameInstance->Print();
		Cast<UHUDMainMenu>(WidgetMainMenu)->SetPlayerName(LoadGameInstance->PlayPfofile.PlayerName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("fail load"));
	}
}

void USteamTestGameInstance::SaveGame()
{
	auto SaveGameInstance = Cast<USG_PlayerProfile>(UGameplayStatics::CreateSaveGameObject(USG_PlayerProfile::StaticClass()));

	SaveGameInstance->SetPlayerName(PlayerInfo->PlayerName);
	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, PlayerProfileSlot, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("success"));
	}
}

void USteamTestGameInstance::MakePlayerInfo(FString name)
{
	PlayerInfo->PlayerName = name;
}

void USteamTestGameInstance::ChangeConnectionType()
{
	if (IsLanConnection)
	{
		IsLanConnection = false;
	}
	else
	{
		IsLanConnection = true;
	}
}

void USteamTestGameInstance::CreateSession()
{
	 //OnlineSubsystem 받아오기
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// OnlineSubsystem Interface 받아오기
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (OnlineSessionInterface)
		{
			const auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession); // 
			if (ExistingSession != nullptr)
			{
				OnlineSessionInterface->DestroySession(NAME_GameSession);
			}

			OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
			SessionSettings->bIsLANMatch = false;			// Steam을 사용할 것이기 때문에 LanMatch = false
			SessionSettings->NumPublicConnections = 4;		// 세션에 연결 가능한 인원
			SessionSettings->bAllowJoinInProgress = true;	// 세션이 실행 중(게임 중) 참여가능 여부
			SessionSettings->bAllowJoinViaPresence = true;	// 정확하지 않음 - Steam 사용자와 같은 지역에서 참여 가능 여부
			SessionSettings->bShouldAdvertise = true;		// Steam을 통해 세션을 알린다.(다른 플레이어가 해당 세션을 찾아 참여 가능)
			SessionSettings->bUsesPresence = true;			// 정확하지 않음 - Steam 사용자와 같은 지역에서 세션을 찾을 수 있는 여부
			SessionSettings->bUseLobbiesIfAvailable = true; // Lobby API를 지원할 경우 Lobby 사용 여부
			SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); // 세션의 MatchType을 모두에게 열림, 온라인서비스와 핑을 통해 세션 홍보 옵션으로 설정
			
			const ULocalPlayer* Localplayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->CreateSession(*Localplayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
		}
	}
}

void USteamTestGameInstance::FindSession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// OnlineSubsystem Interface 받아오기
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (OnlineSessionInterface)
		{
			// Find Session Complete Delegate 등록
			OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegate);

			// Find Game Session
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->MaxSearchResults = 10000;	// 검색 결과로 나오는 세션 수 최대값
			SessionSearch->bIsLanQuery = false;			// LAN 사용 여부
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); // 찾을 세션 쿼리를 현재로 설정한다

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
		}
	}
}

void USteamTestGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful) // 세션 생성 성공
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15,
				FColor::Blue,
				FString::Printf(TEXT("session create: %s"), *SessionName.ToString()));
		}
	}
	else	// 세션 생성 실패
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15,
				FColor::Red,
				FString::Printf(TEXT("fail session crate")));
		}
	}
}

void USteamTestGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString(TEXT("======== Search Result ========")));
	}


	UE_LOG(LogTemp, Warning, TEXT("Num: %d"), SessionSearch->SearchResults.Num());

	for (auto Result : SessionSearch->SearchResults)
	{

		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;

		// 매치 타입 확인하기
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

		// 찾은 세션의 정보 출력하기
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session ID : %s / Owner : %s"), *Id, *User));
		}

		// 세션의 매치 타입이 "FreeForAll"일 경우 세션 참가
		//if (MatchType == FString("FreeForAll"))
		//{
		//	if (GEngine)
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining Match Type : %s"), *MatchType));
		//	}

		//	// Join Session Complete Delegate 등록 
		//	OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);


		//	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		//	OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		//}
	}
}
