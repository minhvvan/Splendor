

#include "PCPlay.h"
#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "HUDDesk.h"
#include "Tile.h"
#include "Token.h"
#include "Card.h"
#include "GlobalConst.h"

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
	Super::BeginPlay();

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


void APCPlay::Click()
{
	if (IsLocalController())
	{
		if (!IsTurn)
		{
			SendMessage(UGlobalConst::MsgNotTurn);
			return;
		}

		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			auto HittedActor = HitResult.GetActor();
			if (HittedActor->IsA<AToken>())
			{
				auto Token = Cast<AToken>(HitResult.GetActor());
				if (Token) TokenClicked(Token);
			}
			else if (HittedActor->IsA<ACard>())
			{
				auto Card = Cast<ACard>(HitResult.GetActor());
				if (Card) CardClicked(Card);
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

void APCPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APCPlay, IsTurn);
}

void APCPlay::BindState()
{
	if (IsLocalController())
	{
		if (WidgetDesk && IsValid(WidgetDesk))
		{
			WidgetDesk->BindState(GetPlayerState<APSPlayerInfo>());
		}
	}
}

//!------------Turn----------------
void APCPlay::SRSetTurn_Implementation()
{
	auto PS = GetPlayerState<APSPlayerInfo>();

	if (PS)
	{
		auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

		//GS Update
		if (GM)
		{
			GM->InitPlayerTurn(this, PS->GetBFirst());
		}
	}
}

void APCPlay::SetTurn(bool flag)
{
	IsTurn = flag;
}

void APCPlay::SREndTurn_Implementation()
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	check(IsValid(GM));
	GM->EndCurrentTurn();
}

//!------------Token----------------
void APCPlay::SRClickToken_Implementation(AToken* ClickedToken, int cnt, bool bAble)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->TokenClicked(ClickedToken, cnt, bAble);
	}
}

void APCPlay::SRPossessTokens_Implementation(bool bFirst)
{
	GoldCnt = 0;
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->PossessTokens(this, bFirst);

		//Client PC Reset
		ClearSelectedTokens();
	}
}

void APCPlay::ClearSelectedTokens_Implementation()
{
	SelectedToken.Reset();
}

void APCPlay::SRRestoreToken_Implementation(const FTokenCountList& Restore)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		//Tokenmanager
		//전달받은 개수 만큼 반환
		GM->RestoreTokens(Restore, this);
	}
}

void APCPlay::TokenClicked(AToken* ClickedToken)
{
	//연속 여부 판단
	if (SelectedToken.Num() != 0)
	{
		int tokenIdx = ClickedToken->GetIndex();
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
			SendMessage(UGlobalConst::MsgNotContiue);
			return;
		}
	}

	//not selected
	if (SelectedToken.Find(ClickedToken) == INDEX_NONE)
	{
		//3개 over
		if (SelectedToken.Num() >= 3)
		{
			SendMessage(UGlobalConst::MsgThreeToken);
			return;
		}

		//황금토큰 check
		if (ClickedToken->GetTokenType() == ETokenColor::E_Gold)
		{
			if (GoldCnt > 0)
			{
				SendMessage(UGlobalConst::MsgOneGold);
				return;
			}

			if (SelectedToken.Num() != 0)
			{
				SendMessage(UGlobalConst::MsgUnableGold);
				return;
			}

			GoldCnt++;
		}
		else
		{
			if (GoldCnt > 0)
			{
				SendMessage(UGlobalConst::MsgOneGold);
				return;
			}
		}

		SelectedToken.AddUnique(ClickedToken);
		SRClickToken(ClickedToken, SelectedToken.Num(), true);
	}
	else
	{
		if (ClickedToken->GetTokenType() == ETokenColor::E_Gold) GoldCnt--;

		//해제
		SRClickToken(ClickedToken, SelectedToken.Num(), false);
		SelectedToken.Remove(ClickedToken);
	}
}

void APCPlay::TakeTokenFromOpp(ETokenColor color)
{
	//창닫기
	if (WidgetDesk)
	{
		WidgetDesk->CloseItemWidget(EItem::I_TakeToken);
	}

	//  + (SR)토큰 가져오기 
	SRTakeToken(color);
}

void APCPlay::GetTokenByIdx(int idx)
{
	check(IsValid(WidgetDesk));

	WidgetDesk->CloseItemWidget(EItem::I_GetToken);

	SRGetToken(idx);
}

void APCPlay::SRTakeToken_Implementation(ETokenColor color)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->TakeToken(this, color);
	}
}

void APCPlay::SRGetToken_Implementation(int idx)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->GetTokenByIdx(this, idx);
	}
}

void APCPlay::SRFillToken_Implementation()
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	check(IsValid(GM));

	GM->FillToken(this);
}

TArray<FTokenCount> APCPlay::GetOppTokens()
{
	bool bFirst = GetPlayerState<APSPlayerInfo>()->GetBFirst();

	TArray<FTokenCount> result;

	auto GS = GetWorld()->GetGameState<AGSPlay>();
	if (GS)
	{
		for (auto PS : GS->PlayerArray)
		{
			auto cated = Cast<APSPlayerInfo>(PS);
			if (bFirst != cated->GetBFirst())
			{
				result = cated->GetOwnTokens();
			}
		}
	}

	return result;
}

void APCPlay::AddCardToHand_Implementation()
{
	check(IsValid(WidgetDesk));
	WidgetDesk->PopUpSelectCard();
}

//!------------Card----------------
void APCPlay::CardClicked(ACard* ClickedCard)
{
	if (IsLocalController())
	{
		if (WidgetDesk)
		{
			auto info = ClickedCard->GetInfo();
			WidgetDesk->PopUpDetailCard(ClickedCard);
		}
	}
}

void APCPlay::SRBuyCard_Implementation(FCardInfo cardInfo, const FTokenCountList& UseTokens)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->BuyCard(this, cardInfo, UseTokens);
	}
}

void APCPlay::SRChangeCard_Implementation(FCardInfo cardInfo)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	check(IsValid(GM));

	GM->ChangeCard(cardInfo);
}

//!------------Desk----------------
void APCPlay::ShowDesk()
{
	if (IsLocalController())
	{
		if (!WidgetDesk)
		{
			WidgetDesk = Cast<UHUDDesk>(CreateWidget(GetWorld(), DeskClass));
		}

		WidgetDesk->AddToViewport();
		WidgetDesk->BindState(GetPlayerState<APSPlayerInfo>());

		SetInputMode(FInputModeGameAndUI());
		SetShowMouseCursor(true);
	}
}

void APCPlay::PopUpOverToken_Implementation()
{
	if (WidgetDesk)
	{
		WidgetDesk->NotifyOverToken();
	}
}

void APCPlay::SendMessage(FString msg)
{
	if (WidgetDesk)
	{
		WidgetDesk->RenderMessage(msg);
	}
}

void APCPlay::GetCardToHand(FCardInfo Info)
{
	check(IsValid(WidgetDesk));

	WidgetDesk->CloseCardWidget();
	WidgetDesk->AddCardToHand(Info);

	//카드 변경
	SRChangeCard(Info);
}

//!------------Item-----------
void APCPlay::UseItemGetToken_Implementation(const FCardInfo& cardInfo)
{
	check(IsValid(WidgetDesk));

	WidgetDesk->PopUpItemGetToken(cardInfo);
}

void APCPlay::UseItemTakeToken_Implementation()
{
	check(IsValid(WidgetDesk));

	WidgetDesk->PopUpItemTakeToken();
}

void APCPlay::UseItemAnyColor_Implementation(const FCardInfo& cardInfo)
{
	check(IsValid(WidgetDesk));

	WidgetDesk->PopUpItemAnyColor(cardInfo);
}


//!-----------------Crown-------------
void APCPlay::CloseCrownWidget(bool bReplay)
{
	check(IsValid(WidgetDesk));

	WidgetDesk->CloseCrownWidget();

	if (!bReplay)
	{
		SREndTurn();
	}
}

void APCPlay::SRPossessRoyal_Implementation(int key)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	auto PS = GetPlayerState<APSPlayerInfo>();

	check(IsValid(GM) && IsValid(PS));
	GM->UpdateRoyal(key, PS->GetBFirst());
}

//!------------Util--------------
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

void APCPlay::SRAddBonus_Implementation(ETokenColor color)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->AddBonus(color, this);
	}
}

void APCPlay::SRAddScore_Implementation(ETokenColor color, int score)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->AddScore(color, score, this);
	}
}

void APCPlay::SRAddScroll_Implementation()
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->GetScroll(this);
	}
}