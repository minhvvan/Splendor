// Fill out your copyright notice in the Description page of Project Settings.


#include "PCLobby.h"
#include "SteamTestGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.h"
#include "HUDMultMenu.h"
#include "HUDLobby.h"
#include "HUDServerRow.h"
#include "Components/ScrollBox.h"
#include "STGameModeLobby.h"
#include "PSPlayerInfo.h"
#include "GSLobby.h"


APCLobby::APCLobby()
{
	ConstructorHelpers::FClassFinder<UUserWidget> LOBBY(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Lobby.WBP_Lobby_C'"));
	if (LOBBY.Succeeded())
	{
		LobbyClass = LOBBY.Class;
	}
}

void APCLobby::BeginPlay()
{
	if (IsLocalController())
	{
		auto name = GetWorld()->GetMapName();
		if (name == "Lobby")
		{
			ShowLobby();
		}
	}
}

void APCLobby::SRSpawnPlayer_Implementation()
{
	//gamemode 받기
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	GMLobby->SpawnPlayer(this);
}

void APCLobby::ShowLobby()
{
	if (IsLocalController())
	{
		if (!WidgetLobby)
		{
			WidgetLobby = Cast<UHUDLobby>(CreateWidget(GetWorld(), LobbyClass));
		}

		WidgetLobby->AddToViewport();
		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);

		auto PlayerName = GetPlayerState<APSPlayerInfo>()->GetPName();

		SRNotifyEnter(PlayerName);
	}
}

void APCLobby::MarkFirst_Implementation(const FString& name)
{
	if (IsLocalController())
	{
		auto GI = Cast<USteamTestGameInstance>(GetGameInstance());
		GI->SetFirstPlayerName(name);

		if (WidgetLobby)
		{
			WidgetLobby->SetFirstText(name);
		}
	}
}

void APCLobby::MarkSecond_Implementation(const FString& name)
{
	if (IsLocalController())
	{
		if (WidgetLobby)
		{
			WidgetLobby->SetSecondText(name);
		}
	}
}

void APCLobby::SRFirstPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast<ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	auto PS = GetPlayerState<APSPlayerInfo>();

	if (GS->GetFirstPlayer() != nullptr && GS->GetFirstPlayer() != this)
	{
		FailSelect();
		return;
	}

	FString PlayerName;

	//등록 성공
	if (GS->SetFirstPlayer(this))
	{
		PS->SetBFirst(true);
		PlayerName = PS->GetPName();

		Cast<APCLobby>(PS->GetPlayerController())->SuccessSelect();
	}
	else
	{
		PS->SetBFirst(false);
		PlayerName = "";

		Cast<APCLobby>(PS->GetPlayerController())->CancelSelect();
	}

	CheckCanStart();
	GMLobby->FirstPlayerMark(PlayerName);
}

void APCLobby::SRSecondPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	auto PS = GetPlayerState<APSPlayerInfo>();

	if (GS->GetSecondPlayer() != nullptr && GS->GetSecondPlayer() != this)
	{
		FailSelect();
		return;
	}

	FString PlayerName;

	if (GS->SetSecondPlayer(this))
	{
		if (PS)
		{
			PlayerName = PS->GetPName();
			Cast<APCLobby>(PS->GetPlayerController())->SuccessSelect();
		}
	}
	else
	{
		PlayerName = "";
		Cast<APCLobby>(PS->GetPlayerController())->CancelSelect();
	}

	CheckCanStart();

	GMLobby->SecondPlayerMark(PlayerName);
}

void APCLobby::Init_Implementation()
{
	//이거는 player state 따로 관리 하려면 
	// save data에서 정보 뽑아오기
	if (IsLocalController())
	{
		auto GI = Cast<USteamTestGameInstance>(GetGameInstance());
		auto Name = GI->LoadName();
		auto PS = GetPlayerState<APSPlayerInfo>();
		PS->SetPName(Name);

		SRUpdatePlayerState(Name);
	}
}

void APCLobby::SRUpdatePlayerState_Implementation(const FString& name)
{
	auto PS = GetPlayerState<APSPlayerInfo>();
	PS->SetPName(name);
}


void APCLobby::OnRep_PlayerState()
{
	Init();
}

void APCLobby::CheckCanStart()
{
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	for (auto PS : GS->PlayerArray)
	{
		auto PC = Cast<APCLobby>(PS->GetPlayerController());
		PC->EnableCanStart(GS->GetCanStart());
	}
}

void APCLobby::EnableCanStart(bool bStart)
{
	if (WidgetLobby)
	{
		WidgetLobby->SetCanStart(bStart);
	}
}

void APCLobby::SRSendChat_Implementation(const FString& ChatMsg)
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GS = GMLobby->GetGameState<AGSLobby>();

	if (GS)
	{
		for (auto PS : GS->PlayerArray)
		{
			auto PC = Cast<APCLobby>(PS->GetPlayerController());

			if (PC != this)
			{
				PC->RecvChat(ChatMsg);
				break;
			}
		}
	}
}

void APCLobby::RecvChat_Implementation(const FString& ChatMsg)
{
	if (IsLocalController())
	{
		if (WidgetLobby) WidgetLobby->RecvChat(ChatMsg);
	}
}

void APCLobby::SRNotifyEnter_Implementation(const FString& pName)
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GS = GMLobby->GetGameState<AGSLobby>();

	FString NewStr;
	if (pName.IsEmpty())
	{
		NewStr = FString("Player");
		GetPlayerState<APSPlayerInfo>()->SetPName(NewStr);
	}
	else
	{
		NewStr = pName;
	}

	NewStr.Append(UGlobalConst::SuffixEnter);

	if (GS)
	{
		for (auto PS : GS->PlayerArray)
		{
			auto PC = Cast<APCLobby>(PS->GetPlayerController());
			PC->NotifyEnter(NewStr);
		}
	}
}

void APCLobby::NotifyEnter_Implementation(const FString& pName)
{
	if (IsLocalController())
	{
		if (WidgetLobby) WidgetLobby->RecvNoti(pName);
	}
}

void APCLobby::SRStartGame_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMLobby)
	{
		GMLobby->StartGame();
	}

	auto World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/Splendor/Maps/Game/Splendor");
	}
}

void APCLobby::DetachLobbyWidget_Implementation()
{
	if (WidgetLobby)
	{
		WidgetLobby->RemoveFromParent();
	}
}

void APCLobby::SuccessSelect_Implementation()
{
	if (WidgetLobby) WidgetLobby->SuccessSelect();
}

void APCLobby::CancelSelect_Implementation()
{
	if (WidgetLobby) WidgetLobby->CancelSelect();
}

void APCLobby::FailSelect_Implementation()
{
	if (WidgetLobby) WidgetLobby->FailSelect();
}