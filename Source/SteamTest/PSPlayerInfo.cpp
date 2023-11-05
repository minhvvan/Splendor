// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Token.h"
#include "PCPlay.h"
#include "GlobalEnum.h"

APSPlayerInfo::APSPlayerInfo(): PName(""), bFirst(false)
{
	OwnTokens.Init();
	Bonus.Init();
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
	DOREPLIFETIME(APSPlayerInfo, bFirst);

	DOREPLIFETIME(APSPlayerInfo, OwnTokens);
	DOREPLIFETIME(APSPlayerInfo, Bonus);

	DOREPLIFETIME(APSPlayerInfo, ScrollNum);
}

void APSPlayerInfo::AddToken(ETokenColor type)
{
	OwnTokens[type]++;
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

void APSPlayerInfo::OnRep_TotalTokenNum()
{
	OnChangeToken.Broadcast();

	if (TotalTokenNum > 10)
	{
		OnOverToken.Broadcast();
	}
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

int APSPlayerInfo::GetTokenNum(ETokenColor color)
{
	return OwnTokens[color];
}

//!TODO: 변경 필요
void APSPlayerInfo::UpdateTotalToken_Implementation(int num)
{
	TotalTokenNum += num;
	OnChangeToken.Broadcast();
}
