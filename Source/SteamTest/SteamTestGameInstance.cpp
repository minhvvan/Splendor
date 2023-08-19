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
	 //OnlineSubsystem �޾ƿ���
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// OnlineSubsystem Interface �޾ƿ���
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
			SessionSettings->bIsLANMatch = false;			// Steam�� ����� ���̱� ������ LanMatch = false
			SessionSettings->NumPublicConnections = 4;		// ���ǿ� ���� ������ �ο�
			SessionSettings->bAllowJoinInProgress = true;	// ������ ���� ��(���� ��) �������� ����
			SessionSettings->bAllowJoinViaPresence = true;	// ��Ȯ���� ���� - Steam ����ڿ� ���� �������� ���� ���� ����
			SessionSettings->bShouldAdvertise = true;		// Steam�� ���� ������ �˸���.(�ٸ� �÷��̾ �ش� ������ ã�� ���� ����)
			SessionSettings->bUsesPresence = true;			// ��Ȯ���� ���� - Steam ����ڿ� ���� �������� ������ ã�� �� �ִ� ����
			SessionSettings->bUseLobbiesIfAvailable = true; // Lobby API�� ������ ��� Lobby ��� ����
			SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); // ������ MatchType�� ��ο��� ����, �¶��μ��񽺿� ���� ���� ���� ȫ�� �ɼ����� ����
			
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
		// OnlineSubsystem Interface �޾ƿ���
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (OnlineSessionInterface)
		{
			// Find Session Complete Delegate ���
			OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegate);

			// Find Game Session
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->MaxSearchResults = 10000;	// �˻� ����� ������ ���� �� �ִ밪
			SessionSearch->bIsLanQuery = false;			// LAN ��� ����
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); // ã�� ���� ������ ����� �����Ѵ�

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
		}
	}
}

void USteamTestGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful) // ���� ���� ����
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
	else	// ���� ���� ����
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

		// ��ġ Ÿ�� Ȯ���ϱ�
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

		// ã�� ������ ���� ����ϱ�
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session ID : %s / Owner : %s"), *Id, *User));
		}

		// ������ ��ġ Ÿ���� "FreeForAll"�� ��� ���� ����
		//if (MatchType == FString("FreeForAll"))
		//{
		//	if (GEngine)
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining Match Type : %s"), *MatchType));
		//	}

		//	// Join Session Complete Delegate ��� 
		//	OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);


		//	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		//	OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		//}
	}
}
