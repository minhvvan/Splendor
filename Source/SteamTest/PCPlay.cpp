// Fill out your copyright notice in the Description page of Project Settings.


#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "HUDDesk.h"
#include "Camera/CameraActor.h"
#include "Tile.h"


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

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	for (auto cam : FoundActors)
	{
		if (cam->ActorHasTag(FName(*CAM_TAG)))
		{
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