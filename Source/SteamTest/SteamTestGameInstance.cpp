// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamTestGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SG_PlayerProfile.h"
#include "HUDMainMenu.h"
#include "HUDMultMenu.h"
#include "HUDServerRow.h"
#include "Math/IntPoint.h"
#include "HUDLobby.h"
#include "PCMenu.h"
#include "PCLobby.h"
#include "PSPlayerInfo.h"


USteamTestGameInstance::USteamTestGameInstance(): OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
												, OnFindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
												, OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete))
{
	ConstructorHelpers::FClassFinder<UUserWidget> MAIN(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_MainMenu.WBP_MainMenu_C'"));
	if (MAIN.Succeeded())
	{
		MainMenuClass = MAIN.Class;
	}	
	
	ConstructorHelpers::FClassFinder<UUserWidget> ROW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_ServerRow.WBP_ServerRow_C'"));
	if (ROW.Succeeded())
	{
		ServerRowClass = ROW.Class;
	}
}

void USteamTestGameInstance::ShowMainMenu()
{
	if (!WidgetMainMenu)
	{
		WidgetMainMenu = Cast<UHUDMainMenu>(CreateWidget(GetWorld(), MainMenuClass));
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

void USteamTestGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerProfileSlot, 0))
	{
		auto LoadGameInstance = Cast<USG_PlayerProfile>(UGameplayStatics::LoadGameFromSlot(PlayerProfileSlot, 0));

		if (LoadGameInstance)
		{
			if (WidgetMainMenu)
			{
				WidgetMainMenu->SetPlayerName(LoadGameInstance->PlayPfofile.PlayerName);
			}
		}
	}
}

FString USteamTestGameInstance::LoadName()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerProfileSlot, 0))
	{
		auto LoadGameInstance = Cast<USG_PlayerProfile>(UGameplayStatics::LoadGameFromSlot(PlayerProfileSlot, 0));

		if (LoadGameInstance)
		{
			return LoadGameInstance->PlayPfofile.PlayerName;
		}
	}

	return FString();
}

void USteamTestGameInstance::SaveGame()
{
	auto SaveGameInstance = Cast<USG_PlayerProfile>(UGameplayStatics::CreateSaveGameObject(USG_PlayerProfile::StaticClass()));
	APlayerController* const PlayerController = GetFirstLocalPlayerController();
	auto PS = PlayerController->GetPlayerState<APSPlayerInfo>();

	if (PS)
	{
		SaveGameInstance->SetPlayerName(PS->GetPName());
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, PlayerProfileSlot, 0))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("success: %s"), *(PS->GetName())));
		}
	}
}

void USteamTestGameInstance::CreateSession()
{
	 //OnlineSubsystem 받아오기
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// OnlineSubsystem Interface 받아오기
		if (!OnlineSessionInterface)
		{
			OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		}

		const auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
		if (ExistingSession != nullptr)
		{
			OnlineSessionInterface->DestroySession(NAME_GameSession);
		}

		OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("Name: %s"), *OnlineSubsystem->GetSubsystemName().ToString()));

		TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
		SessionSettings->bIsLANMatch = false;			// Steam을 사용할 것이기 때문에 LanMatch = false
		SessionSettings->NumPublicConnections = 2;		// 세션에 연결 가능한 인원
		SessionSettings->bAllowJoinInProgress = true;	// 세션이 실행 중(게임 중) 참여가능 여부
		SessionSettings->bAllowJoinViaPresence = true;	// 정확하지 않음 - Steam 사용자와 같은 지역에서 참여 가능 여부
		SessionSettings->bShouldAdvertise = true;		// Steam을 통해 세션을 알린다.(다른 플레이어가 해당 세션을 찾아 참여 가능)
		SessionSettings->bUsesPresence = true;			// 정확하지 않음 - Steam 사용자와 같은 지역에서 세션을 찾을 수 있는 여부
		SessionSettings->bUseLobbiesIfAvailable = true; // Lobby API를 지원할 경우 Lobby 사용 여부
		SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); // 세션의 MatchType을 모두에게 열림, 온라인서비스와 핑을 통해 세션 홍보 옵션으로 설정

		const ULocalPlayer* Localplayer = GetWorld()->GetFirstLocalPlayerFromController();
		OnlineSessionInterface->CreateSession(*Localplayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);


		OnlineSessionInterface->RegisterPlayer(NAME_GameSession, *Localplayer->GetPreferredUniqueNetId(), false);
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

void USteamTestGameInstance::JoinSession(int32 idx)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (OnlineSessionInterface)
		{
			// Set the Handle again
			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			JoinedSessionName = FName(SessionSearch->SearchResults[idx].Session.OwningUserName);
			auto Result = SessionSearch->SearchResults[idx];
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

void USteamTestGameInstance::LeaveSession()
{
	if (OnlineSessionInterface)
	{
		//NOT WORK
		if (!OnlineSessionInterface->DestroySession(NAME_GameSession))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Fail Destory: %s"), *(JoinedSessionName.ToString())));
		}

		APlayerController* const PlayerController = GetFirstLocalPlayerController();
		PlayerController->ClientTravel("/Game/Splendor/Maps/Menu/MainMenu", ETravelType::TRAVEL_Absolute);
	}
}

void USteamTestGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful) // 세션 생성 성공
	{
		//! Lobby로 이동
		auto Controller = Cast<APCMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller)
		{
			Controller->WidgetMultMenu->RemoveFromParent();
		}

		JoinedSessionName = SessionName;
		auto CreatedSession = OnlineSessionInterface->GetNamedSession(SessionName);
		CreatedSession->OwningUserName = Controller->GetPlayerState<APSPlayerInfo>()->GetPName();

		EnableListenServer(true, 7777);
		auto World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Splendor/Maps/Menu/Lobby?listen");
		}
	}
	else	// 세션 생성 실패
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("fail session crate")));
		OnCreateSessionCompleteDelegate.Unbind();
		//! 오류 메시지 팝업
	}
}

void USteamTestGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	OnFindSessionCompleteDelegate.Unbind();

	auto Controller = Cast<APCMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (bWasSuccessful)
	{
		for (auto Result : SessionSearch->SearchResults)
		{
			auto ServerRow = Cast<UHUDServerRow>(CreateWidget(GetWorld(), ServerRowClass));

			int max = Result.Session.SessionSettings.NumPublicConnections;
			int current = Result.Session.NumOpenPublicConnections;

			ServerRow->SetServerName(Result.Session.OwningUserName);
			ServerRow->SetNumPlayer(current, max);
			ServerRow->SetPing(Result.PingInMs);

			Controller->AddSessionRow(ServerRow);
		}
	}
	else
	{
		Controller->FailedSearch();
	}
}

void USteamTestGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			APlayerController* const PlayerController = GetFirstLocalPlayerController();
			FString TravelURL;

			if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
			{
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}