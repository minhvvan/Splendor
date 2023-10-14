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
#include "Net/UnrealNetwork.h"

APCPlay::APCPlay()
{
	EnableInput(this);

	ConstructorHelpers::FClassFinder<UUserWidget> DESK(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Desk.WBP_Desk_C'"));
	if (DESK.Succeeded())
	{
		DeskClass = DESK.Class;
	}

	bReplicates = true;
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

			if (IsTurn)
			{
				if (Token)
				{
					//연속 여부 판단
					if (SelectedToken.Num() != 0)
					{
						int tokenIdx = Token->GetIndex();
						bool flag = false;
						for (auto selectedToken : SelectedToken)
						{
							if (tokenIdx == selectedToken->GetIndex())
							{
								flag = true;
								break;
							}

							if (IsNear(tokenIdx, selectedToken->GetIndex()))
							{
								flag = true;
								break;
							}
						}

						if (!flag)
						{
							if (WidgetDesk)
							{
								WidgetDesk->RenderMessage(FString::Printf(TEXT("연속하지 않은 토큰입니다.")));
							}
							return;
						}
					}

					if (SelectedToken.Find(Token) == INDEX_NONE)
					{
						if (SelectedToken.Num() < 3)
						{
							SelectedToken.AddUnique(Token);
							SRClickToken(Token, SelectedToken.Num(), true);
						}
						else
						{
							if (WidgetDesk)
							{
								WidgetDesk->RenderMessage(FString::Printf(TEXT("토큰은 3개까지 선택할 수 있습니다.")));
							}
						}
					}
					else
					{
						//해제
						SRClickToken(Token, SelectedToken.Num(), false);
						SelectedToken.Remove(Token);
					}
				}
			}
			else
			{
				if (WidgetDesk)
				{
					WidgetDesk->RenderMessage(FString::Printf(TEXT("당신의 차례가 아닙니다.")));
				}
			}
		}
	}
}

bool APCPlay::IsNear(int a, int b)
{
	int minVal = a < b ? a : b;
	int maxVal = a > b ? a : b;

	int diff = maxVal - minVal;

	if (minVal % 5 == 0)
	{
		if (diff == 1 || diff == 5 || diff == 6)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (minVal % 5 == 4)
	{
		if (diff == 4 || diff == 5)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (diff == 1 || diff == 4 || diff == 5 || diff == 6)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
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

void APCPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APCPlay, IsTurn);
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
			GM->InitPlayerTurn(this, PS->GetMyTurn());
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

void APCPlay::SRPossessTokens_Implementation()
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->PossessTokens(this);

		//Client PC Reset
		ClearSelectedTokens();
	}
}

void APCPlay::ClearSelectedTokens_Implementation()
{
	SelectedToken.Reset();
}