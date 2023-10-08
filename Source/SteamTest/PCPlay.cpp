// Fill out your copyright notice in the Description page of Project Settings.


#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "HUDDesk.h"
#include "Camera/CameraActor.h"
#include "Tile.h"
#include "Token.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

APCPlay::APCPlay()
{
	EnableInput(this);

	ConstructorHelpers::FClassFinder<UUserWidget> DESK(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Desk.WBP_Desk_C'"));
	if (DESK.Succeeded())
	{
		DeskClass = DESK.Class;
	}

	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
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

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
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
	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);
}

void APCPlay::Click()
{
	if (IsLocalController())
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			auto Token = Cast<AToken>(HitResult.GetActor());

			if (Token)
			{
				if (SelectedToken.Find(Token) == INDEX_NONE)
				{
					if (SelectedToken.Num() < 3)
					{ 
						SelectedToken.AddUnique(Token);
						SRClickToken(Token, SelectedToken.Num(), true);
					}
					else
					{
						//!TODO: 안내문구
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("already 3")));
					}
				}
				else
				{
					SelectedToken.Remove(Token);
					SRClickToken(Token, SelectedToken.Num(), false);
				}

				if (SelectedToken.Num() == 0)
				{
					// GetToken unable
					if (WidgetDesk)
					{
						WidgetDesk->SetBtnGetTokenState(false);
					}
				}
				else
				{
					//GetToken enable
					if (WidgetDesk)
					{
						WidgetDesk->SetBtnGetTokenState(true);
					}
				}
			}
		}
	}
}

void APCPlay::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &APCPlay::Click);
	}
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


void APCPlay::SRClickToken_Implementation(AToken* ClickedToken, int cnt, bool bAble)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->TokenClicked(ClickedToken, cnt, bAble);
	}
}