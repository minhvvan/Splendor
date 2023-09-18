// Fill out your copyright notice in the Description page of Project Settings.


#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "HUDDesk.h"
#include "Camera/CameraActor.h"


APCPlay::APCPlay()
{
	ConstructorHelpers::FClassFinder<UUserWidget> DESK(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Desk.WBP_Desk_C'"));
	if (DESK.Succeeded())
	{
		DeskClass = DESK.Class;
	}
}

void APCPlay::BeginPlay()
{
	ShowDesk();

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("BeginPlay")));

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	for (auto cam : FoundActors)
	{
		if (cam->ActorHasTag(FName(*CAM_TAG)))
		{

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Cam")));

			SetViewTargetWithBlend(Cast<AActor>(cam));
		}
	}
}

void APCPlay::SeamlessTravelFrom(APlayerController* OldPC)
{
	Super::SeamlessTravelFrom(OldPC);

	SRSetTurn();
}

void APCPlay::ShowDesk()
{
	if (!WidgetDesk)
	{
		WidgetDesk = Cast<UHUDDesk>(CreateWidget(GetWorld(), DeskClass));
	}

	WidgetDesk->AddToViewport();
	//SetInputMode(FInputModeGameOnly());
	//SetShowMouseCursor(false);
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

//void APCPlay::SpawnPlayer_Implementation()
//{
//	UWorld* world = GetWorld();
//	if (world)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SpawnPlayer")));
//
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.Owner = this;
//		FRotator rotator;
//		FVector loc = FVector(0, -90, 1200);
//
//
//		auto pawn = Cast<APawn>(world->SpawnActor<AActor>(PawnClass, loc, rotator, SpawnParams));
//		Possess(pawn);
//	}
//}


void APCPlay::SRSetTurn_Implementation()
{
	auto PS = GetPlayerState<APSPlayerInfo>();
	
	if (PS)
	{
		auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

		//GS Update
		if (GM)
		{
			GM->SetPlayerTurn(this, PS->GetMyTurn());
		}
	}
}
