// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDesk.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUDCardHolder.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"
#include "Token.h"

void UHUDDesk::NativeOnInitialized()
{
	BtnGetToken->OnClicked.AddDynamic(this, &UHUDDesk::GetTokenClicked);
	BtnFillToken->OnClicked.AddDynamic(this, &UHUDDesk::FilTokenClicked);
}

void UHUDDesk::SetScoreTxt(int score)
{
}

void UHUDDesk::SetCrownTxt(int crown)
{
}

void UHUDDesk::SetScrollTxt(int scroll)
{
}

void UHUDDesk::SetTurnTxt(FString turn)
{
}

void UHUDDesk::SetBtnGetTokenState(bool bEnable)
{
	if (bEnable)
	{
		BtnGetToken->SetIsEnabled(true);
	}
	else
	{
		BtnGetToken->SetIsEnabled(false);
	}
}

void UHUDDesk::GetTokenClicked()
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());

	if (PC)
	{
		auto Tokens = PC->GetSelectedTokens();

		Tokens.Sort([](const AToken& A, const AToken& B) {
			return A.GetIndex() < B.GetIndex();
		});

		//상하 : 5
		bool flag = true;

		int diff = -1;
		int prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex(); 
				continue;
			}

			if (diff == -1)
			{
				diff = token->GetIndex() - prev;
			}
			else
			{
				if (diff != token->GetIndex() - prev)
				{
					flag = false;
					break;
				}
			}

			prev = token->GetIndex();
		}
		
		if (flag)
		{
			// Get
			//PossessTokens -> TokenManager(token move) -> TileManager(select 정리)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Success")));
			PC->SRPossessTokens();

			//턴 종료 
			//EndTurn -> Turn Switch

			return;
		}

		//error 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Fail")));
	}
}

void UHUDDesk::FilTokenClicked()
{
}
