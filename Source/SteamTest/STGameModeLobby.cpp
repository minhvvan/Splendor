// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModeLobby.h"
#include "SteamTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SteamTestGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PCMenu.h"
#include "PCLobby.h"
#include "PSPlayerInfo.h"
#include "GSLobby.h"

ASTGameModeLobby::ASTGameModeLobby()
{
	bUseSeamlessTravel = true;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Script/Engine.Blueprint'/Game/Framework/BP_PCLobby.BP_PCLobby_C'"));
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}

	DefaultPawnClass = nullptr;
}

void ASTGameModeLobby::BeginPlay()
{
}

void ASTGameModeLobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	///서버는 되는데 client player state를 못가져옴
	///뭔가 PC 복사 때문인거 같은데 
	/// 
	/// RPC(client) get data -> save game으로 불러와서 -> RPC(server)update
	//Cast<APCLobby>(NewPlayer)->Init();


	//PlayerControllers.Add(NewPlayer);
	//PlayerStates.Add(NewPlayer->GetPlayerState<APSPlayerInfo>());


}

void ASTGameModeLobby::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
	//server 단위 travel 
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SwapPlayerControllers")));

	//PlayerControllers.Add(NewPC);
	//PlayerStates.Add(NewPC->GetPlayerState<APSPlayerInfo>());
}

void ASTGameModeLobby::Logout(AController* Exiting)
{
	auto PCtarget = Cast<APCMenu>(Exiting);

	//PlayerControllers.Remove(PCtarget);
	//PlayerStates.Remove(PCtarget->GetPlayerState<APSPlayerInfo>());
}

void ASTGameModeLobby::SpawnPlayer(APlayerController* PlayerController)
{
	//if (IsValid(PlayerController))
	//{
	//	auto Pawn = PlayerController->GetPawn();
	//	if (Pawn)
	//	{
	//		Pawn->Destroy();
	//	}
	//}

	//pawn spawn해야됨
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("spawn palyer")));
}

void ASTGameModeLobby::FirstPlayerMark(FString name, bool bEnableFirst)
{
	auto GS = GetGameState<AGSLobby>();

	for (auto PlayerState : GS->PlayerArray)
	{
		Cast<APCLobby>(PlayerState->GetPlayerController())->MarkFirst(name, bEnableFirst);
	}
}

void ASTGameModeLobby::SecondPlayerMark(FString name, bool bEnableSecond)
{
	auto GS = GetGameState<AGSLobby>();

	for (auto PlayerState : GS->PlayerArray)
	{
		Cast<APCLobby>(PlayerState->GetPlayerController())->MarkSecond(name, bEnableSecond);
	}
}
