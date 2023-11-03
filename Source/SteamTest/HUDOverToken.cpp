// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDOverToken.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Token.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

void UHUDOverToken::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	BtnRedUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpRed);
	BtnRedDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownRed);

	BtnGreenUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpGreen);
	BtnGreenDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownGreen);

	BtnBlueUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpBlue);
	BtnBlueDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownBlue);

	BtnWhiteUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpWhite);
	BtnWhiteDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownWhite);

	BtnBlackUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpBlack);
	BtnBlackDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownBlack);

	BtnGoldUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpGold);
	BtnGoldDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownGold);

	BtnPearlUp->OnClicked.AddDynamic(this, &UHUDOverToken::UpPearl);
	BtnPearlDown->OnClicked.AddDynamic(this, &UHUDOverToken::DownPearl);

	BtnCommit->OnClicked.AddDynamic(this, &UHUDOverToken::CommitTokens);

	auto player = GetOwningPlayer<APCPlay>();
	if (player)
	{
		PS = player->GetPlayerState<APSPlayerInfo>();
		if (PS)
		{
			RedNum = PS->GetTokenRed();
			GreenNum = PS->GetTokenGreen();
			BlueNum = PS->GetTokenBlue();
			WhiteNum = PS->GetTokenWhite();
			BlackNum = PS->GetTokenBlack();
			GoldNum = PS->GetTokenGold();
			PearlNum = PS->GetTokenPearl();

			TxtRed->SetText(FText::AsNumber(RedNum));
			TxtGreen->SetText(FText::AsNumber(GreenNum));
			TxtBlue->SetText(FText::AsNumber(BlueNum));
			TxtWhite->SetText(FText::AsNumber(WhiteNum));
			TxtBlack->SetText(FText::AsNumber(BlackNum));
			TxtGold->SetText(FText::AsNumber(GoldNum));
			TxtPearl->SetText(FText::AsNumber(PearlNum));

			TotalNum = RedNum + GreenNum + BlueNum + WhiteNum + BlackNum + GoldNum + PearlNum;
			TxtCurrentToken->SetText(FText::AsNumber(TotalNum));
		}
	}
}

void UHUDOverToken::UpRed()
{
	if (PS)
	{
		if (RedNum < PS->GetTokenRed())
		{
			RedNum++;
			TxtRed->SetText(FText::AsNumber(RedNum));
		}
		else
		{
			FailClick(ETokenType::T_Red, true);
		}

		UpdateTotalToken();
	}
}

void UHUDOverToken::DownRed()
{
	if (RedNum > 0)
	{
		RedNum--;
		TxtRed->SetText(FText::AsNumber(RedNum));
	}
	else
	{
		FailClick(ETokenType::T_Red, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpGreen()
{
	if (GreenNum < PS->GetTokenGreen())
	{
		GreenNum++;
		TxtGreen->SetText(FText::AsNumber(GreenNum));
	}
	else
	{
		FailClick(ETokenType::T_Green, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownGreen()
{
	if (GreenNum > 0)
	{
		GreenNum--;
		TxtGreen->SetText(FText::AsNumber(GreenNum));
	}
	else
	{
		FailClick(ETokenType::T_Green, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpBlue()
{
	if (BlueNum < PS->GetTokenBlue())
	{
		BlueNum++;
		TxtBlue->SetText(FText::AsNumber(BlueNum));
	}
	else
	{
		FailClick(ETokenType::T_Blue, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownBlue()
{
	if (BlueNum > 0)
	{
		BlueNum--;
		TxtBlue->SetText(FText::AsNumber(BlueNum));
	}
	else
	{
		FailClick(ETokenType::T_Blue, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpWhite()
{
	if (WhiteNum < PS->GetTokenWhite())
	{
		WhiteNum++;
		TxtWhite->SetText(FText::AsNumber(WhiteNum));
	}
	else
	{
		FailClick(ETokenType::T_White, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownWhite()
{
	if (WhiteNum > 0)
	{
		WhiteNum--;
		TxtWhite->SetText(FText::AsNumber(WhiteNum));
	}
	else
	{
		FailClick(ETokenType::T_White, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpBlack()
{
	if (BlackNum < PS->GetTokenBlack())
	{
		BlackNum++;
		TxtBlack->SetText(FText::AsNumber(BlackNum));
	}
	else
	{
		FailClick(ETokenType::T_Black, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownBlack()
{
	if (BlackNum > 0)
	{
		BlackNum--;
		TxtBlack->SetText(FText::AsNumber(BlackNum));
	}
	else
	{
		FailClick(ETokenType::T_Black, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpGold()
{
	if (GoldNum < PS->GetTokenGold())
	{
		GoldNum++;
		TxtGold->SetText(FText::AsNumber(GoldNum));
	}
	else
	{
		FailClick(ETokenType::T_Gold, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownGold()
{
	if (GoldNum > 0)
	{
		GoldNum--;
		TxtGold->SetText(FText::AsNumber(GoldNum));
	}
	else
	{
		FailClick(ETokenType::T_Gold, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpPearl()
{
	if (PearlNum < PS->GetTokenPearl())
	{
		PearlNum++;
		TxtPearl->SetText(FText::AsNumber(PearlNum));
	}
	else
	{
		FailClick(ETokenType::T_Pearl, true);
	}

	UpdateTotalToken();
}

void UHUDOverToken::DownPearl()
{
	if (PearlNum > 0)
	{
		PearlNum--;
		TxtPearl->SetText(FText::AsNumber(PearlNum));
	}
	else
	{
		FailClick(ETokenType::T_Pearl, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::CommitTokens()
{
	if (TotalNum > 10)
	{
		RenderMessage();
		if (FailCommit) PlayAnimation(FailCommit);
		if (FailSound) PlaySound(FailSound);

		return;
	}

	if (PS)
	{
		auto Restore = FRestroeTokens();

		for (ETokenType type : TEnumRange<ETokenType>())
		{
			int current = GetTokenNumByType(type);

			int diff = PS->GetTokenNum(type) - current;
			for (int i = 0; i < diff; i++)
			{
				Restore.RestoreTokens.Add(type);
			}

			PS->SetToken(ETokenType::T_Red, current);
		}

		//서버에 넣어야 됨 -> PC한테 요청
		GetOwningPlayer<APCPlay>()->SRRestoreToken(Restore);
	}

	RemoveFromParent();
}

void UHUDOverToken::UpdateTotalToken()
{
	TotalNum = RedNum + GreenNum + BlueNum + WhiteNum + BlackNum + GoldNum + PearlNum;
	TxtCurrentToken->SetText(FText::AsNumber(TotalNum));

	if (TotalNum > 10)
	{
		TxtCurrentToken->SetColorAndOpacity(FColor::Red);
	}
	else
	{
		TxtCurrentToken->SetColorAndOpacity(FColor::White);
	}
}

int UHUDOverToken::GetTokenNumByType(ETokenType type)
{
	switch (type)
	{
	case ETokenType::T_Red:
		return RedNum;
	case ETokenType::T_Green:
		return GreenNum;
	case ETokenType::T_Blue:
		return BlueNum;
	case ETokenType::T_White:
		return WhiteNum;
	case ETokenType::T_Black:
		return BlackNum;
	case ETokenType::T_Gold:
		return GoldNum;
	case ETokenType::T_Pearl:
		return PearlNum;
	}

	return 0;
}

void UHUDOverToken::FailClick(ETokenType type, bool bUp)
{
	if (bUp)
	{
		switch (type)
		{
		case ETokenType::T_Red:
			if (FailRedUp) PlayAnimation(FailRedUp);
			break;

		case ETokenType::T_Green:
			if (FailGreenUp) PlayAnimation(FailGreenUp);
			break;

		case ETokenType::T_Blue:
			if (FailBlueUp) PlayAnimation(FailBlueUp);
			break;

		case ETokenType::T_White:
			if (FailWhiteUp) PlayAnimation(FailWhiteUp);
			break;

		case ETokenType::T_Black:
			if (FailBlackUp) PlayAnimation(FailBlackUp);
			break;

		case ETokenType::T_Gold:
			if (FailGoldUp) PlayAnimation(FailGoldUp);
			break;

		case ETokenType::T_Pearl:
			if (FailPearlUp) PlayAnimation(FailPearlUp);
			break;
		}
	}
	else
	{
		switch (type)
		{
		case ETokenType::T_Red:
			if (FailRedDown) PlayAnimation(FailRedDown);
			break;

		case ETokenType::T_Green:
			if (FailGreenDown) PlayAnimation(FailGreenDown);
			break;

		case ETokenType::T_Blue:
			if (FailBlueDown) PlayAnimation(FailBlueDown);
			break;

		case ETokenType::T_White:
			if (FailWhiteDown) PlayAnimation(FailWhiteDown);
			break;

		case ETokenType::T_Black:
			if (FailBlackDown) PlayAnimation(FailBlackDown);
			break;

		case ETokenType::T_Gold:
			if (FailGoldDown) PlayAnimation(FailGoldDown);
			break;

		case ETokenType::T_Pearl:
			if (FailPearlDown) PlayAnimation(FailPearlDown);
			break;
		}
	}

	if (FailSound)
	{
		PlaySound(FailSound);
	}
}

void UHUDOverToken::RenderMessage()
{
	if (MessageAnim)
	{
		PlayAnimation(MessageAnim);
	}
}
