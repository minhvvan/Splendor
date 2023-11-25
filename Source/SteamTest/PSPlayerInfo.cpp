// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Token.h"
#include "PCPlay.h"
#include "GlobalEnum.h"

APSPlayerInfo::APSPlayerInfo(): PName(""), bFirst(false), ScrollNum(0), TotalScore(19), Crown(0)
{
	OwnTokens.Init();
	OwnBonus.Init();
	ColorScore.Init();

	NetUpdateFrequency = 5;
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
	DOREPLIFETIME(APSPlayerInfo, bFirst);

	DOREPLIFETIME(APSPlayerInfo, OwnTokens);
	DOREPLIFETIME(APSPlayerInfo, OwnBonus);
	DOREPLIFETIME(APSPlayerInfo, ColorScore);

	DOREPLIFETIME(APSPlayerInfo, ScrollNum);
	DOREPLIFETIME(APSPlayerInfo, TotalScore);
	DOREPLIFETIME(APSPlayerInfo, Crown);
}

void APSPlayerInfo::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (PlayerState)
	{
		APSPlayerInfo* NewPlayerState = Cast<APSPlayerInfo>(PlayerState);
		if (NewPlayerState)
		{
			NewPlayerState->PName = PName;
			NewPlayerState->bFirst = bFirst;
		}
	}
}

void APSPlayerInfo::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		APSPlayerInfo* OldPlayerState = Cast<APSPlayerInfo>(PlayerState);
		if (OldPlayerState)
		{
			PName = OldPlayerState->PName;
			bFirst = OldPlayerState->bFirst;
		}
	}
}

void APSPlayerInfo::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);

	//Called Client PS Replicated
	auto PC = Cast<APCPlay>(GetOwningController());
	if(PC) PC->BindState();
}

void APSPlayerInfo::CheckWin()
{
	if (20 <= TotalScore) OnWinGame.Broadcast(this);
	if (10 <= Crown) OnWinGame.Broadcast(this);

	for (auto color : TEnumRange<ETokenColor>())
	{
		if (10 <= ColorScore[color]) OnWinGame.Broadcast(this);
	}
}

//!-----------------Token---------------------
//Single Uipdate
void APSPlayerInfo::AddToken(ETokenColor type, int cnt)
{
	OwnTokens[type] += cnt;
	OnChangeToken.Broadcast();
}

//Multi Uipdate
void APSPlayerInfo::AddTokenByList(FTokenCountList& tokens)
{
	for (auto token : tokens)
	{
		OwnTokens[token.Key] += token.Value;
	}

	OnChangeToken.Broadcast();

	if (OwnTokens.Num() > 10)
	{
		OnOverToken.Broadcast();
	}
}

void APSPlayerInfo::SetToken(ETokenColor type, int num)
{
	OwnTokens[type] = num;
}

void APSPlayerInfo::PrintToken()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Red: %d"), OwnTokens[ETokenColor::E_Red]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Green: %d"), OwnTokens[ETokenColor::E_Green]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Blue: %d"), OwnTokens[ETokenColor::E_Blue]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("White: %d"), OwnTokens[ETokenColor::E_White]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Black: %d"), OwnTokens[ETokenColor::E_Black]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Gold: %d"), OwnTokens[ETokenColor::E_Gold]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Pearl: %d"), OwnTokens[ETokenColor::E_Pearl]));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("-----------------------------")));
}

int APSPlayerInfo::GetTokenNum(ETokenColor color)
{
	return OwnTokens[color];
}

void APSPlayerInfo::OnRep_Tokens()
{
	OnChangeToken.Broadcast();

	if (OwnTokens.Num() > 10)
	{
		OnOverToken.Broadcast();
	}
}

const TArray<FTokenCount>& APSPlayerInfo::GetOwnTokens()
{
	return OwnTokens.Get();
}

//!-----------------Bonus---------------------
void APSPlayerInfo::AddBonus(ETokenColor color)
{
	OwnBonus[color]++;

	OnChangeBonus.Broadcast();
}

int APSPlayerInfo::GetBonusNum(ETokenColor color)
{
	return OwnBonus[color];
}

void APSPlayerInfo::OnRep_Bonus()
{
	OnChangeBonus.Broadcast();
}


//!-----------------Score---------------------
void APSPlayerInfo::AddScore(ETokenColor color, int s)
{
	TotalScore += s;

	OnChangeScore.Broadcast();

	if (color != ETokenColor::E_End)
	{
		AddColorScore(color, s);
	}
}

void APSPlayerInfo::AddColorScore(ETokenColor color, int s)
{
	ColorScore[color] += s;
	OnChangeColorScore.Broadcast();

}

void APSPlayerInfo::OnRep_TotalScore()
{
	OnChangeScore.Broadcast();
}

void APSPlayerInfo::OnRep_ColorScore()
{
	OnChangeColorScore.Broadcast();
}

//!-----------------Scroll---------------------
void APSPlayerInfo::AddScroll(int num)
{
	ScrollNum += num;
	OnScrollChanged.Broadcast();
}

void APSPlayerInfo::OnRep_Scroll()
{
	//~왜 서버쪽 PS변경시 클라에서 동작?
	OnScrollChanged.Broadcast();
}



//!-----------------Crown---------------------
void APSPlayerInfo::AddCrown(int crown)
{
	Crown += crown;
	OnChangeCrown.Broadcast();

	if (Crown == 3 || Crown == 6)
	{
		OnCrownEvent.Broadcast();
	}
}

void APSPlayerInfo::OnRep_Crown()
{
	OnChangeCrown.Broadcast();

	if (Crown == 3 || Crown == 6)
	{
		OnCrownEvent.Broadcast();
	}
}
