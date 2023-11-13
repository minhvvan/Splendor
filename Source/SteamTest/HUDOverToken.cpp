// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDOverToken.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Token.h"
#include "GlobalEnum.h"
#include "GlobalStruct.h"

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
			RedNum =	PS->GetTokenNum(ETokenColor::E_Red);
			GreenNum =	PS->GetTokenNum(ETokenColor::E_Green);
			BlueNum =	PS->GetTokenNum(ETokenColor::E_Blue);
			WhiteNum =	PS->GetTokenNum(ETokenColor::E_White);
			BlackNum =	PS->GetTokenNum(ETokenColor::E_Black);
			GoldNum =	PS->GetTokenNum(ETokenColor::E_Gold);
			PearlNum =	PS->GetTokenNum(ETokenColor::E_Pearl);

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
		if (RedNum < PS->GetTokenNum(ETokenColor::E_Red))
		{
			RedNum++;
			TxtRed->SetText(FText::AsNumber(RedNum));
		}
		else
		{
			FailClick(ETokenColor::E_Red, true);
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
		FailClick(ETokenColor::E_Red, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpGreen()
{
	if (GreenNum < PS->GetTokenNum(ETokenColor::E_Green))
	{
		GreenNum++;
		TxtGreen->SetText(FText::AsNumber(GreenNum));
	}
	else
	{
		FailClick(ETokenColor::E_Green, true);
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
		FailClick(ETokenColor::E_Green, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpBlue()
{
	if (BlueNum < PS->GetTokenNum(ETokenColor::E_Blue))
	{
		BlueNum++;
		TxtBlue->SetText(FText::AsNumber(BlueNum));
	}
	else
	{
		FailClick(ETokenColor::E_Blue, true);
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
		FailClick(ETokenColor::E_Blue, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpWhite()
{
	if (WhiteNum < PS->GetTokenNum(ETokenColor::E_White))
	{
		WhiteNum++;
		TxtWhite->SetText(FText::AsNumber(WhiteNum));
	}
	else
	{
		FailClick(ETokenColor::E_White, true);
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
		FailClick(ETokenColor::E_White, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpBlack()
{
	if (BlackNum < PS->GetTokenNum(ETokenColor::E_Black))
	{
		BlackNum++;
		TxtBlack->SetText(FText::AsNumber(BlackNum));
	}
	else
	{
		FailClick(ETokenColor::E_Black, true);
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
		FailClick(ETokenColor::E_Black, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpGold()
{
	if (GoldNum < PS->GetTokenNum(ETokenColor::E_Gold))
	{
		GoldNum++;
		TxtGold->SetText(FText::AsNumber(GoldNum));
	}
	else
	{
		FailClick(ETokenColor::E_Gold, true);
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
		FailClick(ETokenColor::E_Gold, false);
	}

	UpdateTotalToken();
}

void UHUDOverToken::UpPearl()
{
	if (PearlNum < PS->GetTokenNum(ETokenColor::E_Pearl))
	{
		PearlNum++;
		TxtPearl->SetText(FText::AsNumber(PearlNum));
	}
	else
	{
		FailClick(ETokenColor::E_Pearl, true);
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
		FailClick(ETokenColor::E_Pearl, false);
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
		auto Restore = FTokenCountList();
		Restore.Init();

		for (ETokenColor type : TEnumRange<ETokenColor>())
		{
			int current = GetTokenNumByType(type);
			int diff = PS->GetTokenNum(type) - current;

			if (diff > 0)
			{
				Restore[type] += diff;
			}
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

int UHUDOverToken::GetTokenNumByType(ETokenColor type)
{
	switch (type)
	{
	case ETokenColor::E_Red:
		return RedNum;
	case ETokenColor::E_Green:
		return GreenNum;
	case ETokenColor::E_Blue:
		return BlueNum;
	case ETokenColor::E_White:
		return WhiteNum;
	case ETokenColor::E_Black:
		return BlackNum;
	case ETokenColor::E_Gold:
		return GoldNum;
	case ETokenColor::E_Pearl:
		return PearlNum;
	}

	return 0;
}

void UHUDOverToken::FailClick(ETokenColor type, bool bUp)
{
	if (bUp)
	{
		switch (type)
		{
		case ETokenColor::E_Red:
			if (FailRedUp) PlayAnimation(FailRedUp);
			break;

		case ETokenColor::E_Green:
			if (FailGreenUp) PlayAnimation(FailGreenUp);
			break;

		case ETokenColor::E_Blue:
			if (FailBlueUp) PlayAnimation(FailBlueUp);
			break;

		case ETokenColor::E_White:
			if (FailWhiteUp) PlayAnimation(FailWhiteUp);
			break;

		case ETokenColor::E_Black:
			if (FailBlackUp) PlayAnimation(FailBlackUp);
			break;

		case ETokenColor::E_Gold:
			if (FailGoldUp) PlayAnimation(FailGoldUp);
			break;

		case ETokenColor::E_Pearl:
			if (FailPearlUp) PlayAnimation(FailPearlUp);
			break;
		}
	}
	else
	{
		switch (type)
		{
		case ETokenColor::E_Red:
			if (FailRedDown) PlayAnimation(FailRedDown);
			break;

		case ETokenColor::E_Green:
			if (FailGreenDown) PlayAnimation(FailGreenDown);
			break;

		case ETokenColor::E_Blue:
			if (FailBlueDown) PlayAnimation(FailBlueDown);
			break;

		case ETokenColor::E_White:
			if (FailWhiteDown) PlayAnimation(FailWhiteDown);
			break;

		case ETokenColor::E_Black:
			if (FailBlackDown) PlayAnimation(FailBlackDown);
			break;

		case ETokenColor::E_Gold:
			if (FailGoldDown) PlayAnimation(FailGoldDown);
			break;

		case ETokenColor::E_Pearl:
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
