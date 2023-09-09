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
		ShowLobby();
	}
}

void APCLobby::SRSpawnPlayer_Implementation()
{
	//gamemode �ޱ�
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	GMLobby->SpawnPlayer(this);
}

void APCLobby::ShowLobby()
{
	if (!WidgetLobby)
	{
		WidgetLobby = Cast<UHUDLobby>(CreateWidget(GetWorld(), LobbyClass));
		WidgetLobby->SetPC(this);
	}

	WidgetLobby->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void APCLobby::FirstPlayerClicked()
{
	if (IsLocalController())
	{
		SRFirstPlayerClicked();
	}
}

void APCLobby::SecondPlayerClicked()
{
	if (IsLocalController())
	{
		SRSecondPlayerClicked();
	}
}


void APCLobby::MarkFirst_Implementation(const FString& name, bool bEnableFirst)
{
	if (IsLocalController())
	{
		if (WidgetLobby)
		{
			WidgetLobby->SetFirstText(name);
			WidgetLobby->SetFirstEnable(bEnableFirst);
		}
	}
}

void APCLobby::MarkSecond_Implementation(const FString& name, bool bEnableSecond)
{
	if (IsLocalController())
	{
		if (WidgetLobby)
		{
			WidgetLobby->SetSecondText(name);
			WidgetLobby->SetSecondEnable(bEnableSecond);
		}
	}
}

void APCLobby::SRFirstPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast<ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	//main���� �Է��� name ����(������ hard)
	//auto PS = GetPlayerState<APSPlayerInfo>();
	//auto PlayerName = PS->GetPlayerName();
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	FString PlayerName;
	bool bEnableFirst;
	if (GS->SetFirstPlayer(this))
	{
		auto PS = GetPlayerState<APSPlayerInfo>();
		if (PS)
		{
			PlayerName = PS->GetPName();
			bEnableFirst = false;
		}
	}
	else
	{
		PlayerName = "";
		bEnableFirst = true;
	}

	if (WidgetLobby)
	{
		WidgetLobby->SetCanStart(GS->GetCanStart());
	}

	GMLobby->FirstPlayerMark(PlayerName, bEnableFirst);
}

void APCLobby::SRSecondPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	//main���� �Է��� name ����(������ hard)
	//auto PS = GetPlayerState<APSPlayerInfo>();
	//auto PlayerName = PS->GetPlayerName();
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	FString PlayerName;
	bool bEnableSecond;

	if (GS->SetSecondPlayer(this))
	{
		auto PS = GetPlayerState<APSPlayerInfo>();
		if (PS)
		{
			PlayerName = PS->GetPName();
			bEnableSecond = false;
		}
	}
	else
	{
		PlayerName = "";
		bEnableSecond = true;
	}

	if (WidgetLobby)
	{
		WidgetLobby->SetCanStart(GS->GetCanStart());
	}

	GMLobby->SecondPlayerMark(PlayerName, bEnableSecond);
}

void APCLobby::Init_Implementation()
{
	//�̰Ŵ� player state ���� ���� �Ϸ��� 
	// save data���� ���� �̾ƿ���
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