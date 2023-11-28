

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
#include "TileManager.h"
#include "TokenManager.h"

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

	if (IsLocalController())
	{
		TileManager = GetWorld()->SpawnActor<ATileManager>();
		TokenManager = GetWorld()->SpawnActor<ATokenManager>();
		InitGameBase();
	}

	//role check 해서 client만 실행하게 하면 될거 같기도 
	if (IsLocalController())
	{
		SRSetTurn();
	}
}


void APCPlay::Click()
{
	if (IsLocalController())
	{
		//if (!IsTurn)
		//{
		//	SendMessage(UGlobalConst::MsgNotTurn);
		//	return;
		//}

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
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &APCPlay::Click);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &APCPlay::PopupRivalInfo);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Completed, this, &APCPlay::CloseRivalInfo);
	}
}

void APCPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APCPlay, IsTurn);
	DOREPLIFETIME(APCPlay, GoldCnt);
	DOREPLIFETIME(APCPlay, SelectedTokenIdx);
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

void APCPlay::PopupRivalInfo()
{
	if (IsLocalController())
	{
		if (WidgetDesk)
		{
			WidgetDesk->PopUpRivalInfo();
		}
	}
}

void APCPlay::CloseRivalInfo()
{
	if (IsLocalController())
	{
		if (WidgetDesk)
		{
			WidgetDesk->CloseRivalInfo();
		}
	}
}

void APCPlay::EndGame_Implementation(const FString& winnerName, bool bWin)
{
	if (WidgetDesk)
	{
		SetInputMode(FInputModeGameAndUI());
		WidgetDesk->PopUpEndPage(winnerName, bWin);
	}
}

//!------------Turn----------------
void APCPlay::SRSetTurn_Implementation()
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->InitPlayerTurn(this);
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
void APCPlay::InitGameBase()
{
	check(IsValid(TokenManager) && IsValid(TileManager));

	auto& Tokens = TokenManager->GetRemainTokens();
	TileManager->SetTokenLocs(Tokens);
}

void APCPlay::SpawnToken_Implementation(const TArray<FTokenIdxColor>& Tokens)
{
	check(IsValid(TokenManager) && IsValid(TileManager));

	auto Spawned = TokenManager->SpawnTokens(Tokens);
	TileManager->SetTokenLocs(Spawned);
}

void APCPlay::PossessTokens()
{
	SRPossessTokens(SelectedTokenIdx);
}

void APCPlay::RemoveTokens_Implementation(const TArray<int>& DestroyTokenIdx, bool bOwn)
{
	if (TileManager)
	{
		TileManager->ClearSeletedTiles(DestroyTokenIdx);
	}

	if (TokenManager)
	{
		TokenManager->DestroyTokens(DestroyTokenIdx, bOwn);
	}
}

void APCPlay::SRPossessTokens_Implementation(const TArray<FTokenIdxColor>& selcted)
{
	GoldCnt = 0;
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->PossessTokens(this, selcted);

		//Client PC Reset
		ClearSelectedTokens();
	}
}

void APCPlay::ClearSelectedTokens_Implementation()
{
	SelectedTokenIdx.Reset();
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
	int tokenIdx = ClickedToken->GetIndex();
	auto tokenColor = ClickedToken->GetTokenType();

	//연속 여부 판단
	if (SelectedTokenIdx.Num() != 0)
	{
		bool flag = false;
		for (auto selectedToken : SelectedTokenIdx)
		{
			if (tokenIdx == selectedToken.Idx)
			{
				flag = true;
				break;
			}

			if (IsNear(tokenIdx, selectedToken.Idx))
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
	if (SelectedTokenIdx.Find({ tokenIdx, tokenColor }) == INDEX_NONE)
	{
		//3개 over
		if (SelectedTokenIdx.Num() >= 3)
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

			if (SelectedTokenIdx.Num() != 0)
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

		SelectedTokenIdx.Add({tokenIdx, tokenColor});

		check(IsValid(TileManager));
		TileManager->Clicked(tokenIdx, true);

		//!TODO: 다른 PC Update
		//SRClickToken();
	}
	else
	{
		if (ClickedToken->GetTokenType() == ETokenColor::E_Gold) GoldCnt--;

		check(IsValid(TileManager));
		TileManager->Clicked(tokenIdx, false);
		SelectedTokenIdx.Remove({ tokenIdx, tokenColor });
	}
}

void APCPlay::TakeTokenFromOpp(ETokenColor color)
{
	//창닫기
	if (WidgetDesk)
	{
		SetInputMode(FInputModeGameAndUI());
		WidgetDesk->CloseItemWidget(EItem::I_TakeToken);
	}

	//  + (SR)토큰 가져오기 
	SRTakeToken(color);
}

void APCPlay::GetTokenByIdx(int idx)
{
	check(IsValid(WidgetDesk));

	SetInputMode(FInputModeGameAndUI());
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

	auto GS = GM->GetGameState<AGSPlay>();
	if (GS->GetPouch().Num() == 0)
	{
		FailFillToken();
		return;
	}

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
	SetInputMode(FInputModeUIOnly());
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
			SetInputMode(FInputModeUIOnly());
			WidgetDesk->PopUpDetailCard(info);
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
		SetInputMode(FInputModeUIOnly());
		WidgetDesk->NotifyOverToken();
	}
}

void APCPlay::SendMessage_Implementation(const FString& msg)
{
	if (WidgetDesk)
	{
		WidgetDesk->RenderMessage(msg);
	}
}

void APCPlay::GetCardToHand(FCardInfo Info)
{
	check(IsValid(WidgetDesk));

	SetInputMode(FInputModeGameAndUI());
	WidgetDesk->CloseCardWidget();
	WidgetDesk->AddCardToHand(Info);

	//카드 변경
	SRChangeCard(Info);
}

void APCPlay::SetTurnText_Implementation(const FString& playerName)
{
	if (WidgetDesk)
	{
		WidgetDesk->IntSetTurnBegin(playerName);
	}
}

void APCPlay::FailFillToken_Implementation()
{
	if (WidgetDesk)
	{
		WidgetDesk->FailAnimPlay(EFailWidget::E_FillToken);
	}
}


//!------------Item-----------
void APCPlay::UseItemGetToken_Implementation(const FCardInfo& cardInfo)
{
	check(IsValid(WidgetDesk));

	TArray<ETokenColor> colors;
	colors.Add(cardInfo.color);

	SetInputMode(FInputModeUIOnly());
	WidgetDesk->PopUpItemGetToken(colors, true);
}

void APCPlay::UseItemTakeToken_Implementation()
{
	check(IsValid(WidgetDesk));

	SetInputMode(FInputModeUIOnly());
	WidgetDesk->PopUpItemTakeToken();
}

void APCPlay::UseItemAnyColor_Implementation(const FCardInfo& cardInfo)
{
	check(IsValid(WidgetDesk));

	SetInputMode(FInputModeUIOnly());
	WidgetDesk->PopUpItemAnyColor(cardInfo);
}


//!-----------------Crown-------------
void APCPlay::CloseCrownWidget(bool bReplay)
{
	check(IsValid(WidgetDesk));

	SetInputMode(FInputModeGameAndUI());
	WidgetDesk->CloseCrownWidget();

	if (!bReplay)
	{
		SREndTurn();
	}
}

void APCPlay::SRPossessRoyal_Implementation(int key)
{
	auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

	check(IsValid(GM));
	GM->UpdateRoyal(key, this);
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

void APCPlay::SRUseScroll_Implementation()
{
	auto PS = GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->AddScroll(-1);
	}
}