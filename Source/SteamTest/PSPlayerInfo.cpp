// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Token.h"
#include "PCPlay.h"
#include "GlobalEnum.h"

APSPlayerInfo::APSPlayerInfo(): PName(""), bFirst(false), bTokenUpdated(false), ScrollNum(0), TotalScore(0)
{
	OwnTokens.Init();
	OwnBonus.Init();
	ColorScore.Init();
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
	DOREPLIFETIME(APSPlayerInfo, bFirst);

	DOREPLIFETIME(APSPlayerInfo, OwnTokens);
	DOREPLIFETIME(APSPlayerInfo, OwnBonus);
	DOREPLIFETIME(APSPlayerInfo, ColorScore);

	DOREPLIFETIME(APSPlayerInfo, bTokenUpdated);
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

	Cast<APCPlay>(GetOwningController())->BindState();
}


//!-----------------Token---------------------
void APSPlayerInfo::AddToken(ETokenColor type, int cnt)
{
	if (bTokenUpdated) bTokenUpdated = false;

	OwnTokens[type] += cnt;
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

void APSPlayerInfo::OnRep_TokenUpdated()
{
	OnChangeToken.Broadcast();

	if (OwnTokens.Num() > 10)
	{
		OnOverToken.Broadcast();
	}
}

void APSPlayerInfo::NotifyUpdateToken_Implementation()
{
	bTokenUpdated = true;
	OnChangeToken.Broadcast();
}


//!-----------------Bonus---------------------
void APSPlayerInfo::AddBonus(ETokenColor color)
{
	OwnBonus[color]++;

	//!TODO: 여기서 boradcast??????
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
	AddColorScore(color, s);
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
}

void APSPlayerInfo::OnRep_Crown()
{
	OnChangeCrown.Broadcast();
}
