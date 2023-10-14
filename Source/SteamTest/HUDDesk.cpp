// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDesk.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUDCardHolder.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"
#include "Token.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"


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

void UHUDDesk::RenderMessage(FText message)
{
	if (TxtMessage)
	{
		TxtMessage->SetText(message);
	}

	if (MessageAnim)
	{
		PlayAnimation(MessageAnim);
	}
}

void UHUDDesk::GetTokenClicked()
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());

	if (PC)
	{
		auto Tokens = PC->GetSelectedTokens();

		if (Tokens.Num() == 0)
		{
			//!message: 토큰을 선택해 주세요.
			if (FailedGetAnim)
			{
				PlayAnimation(FailedGetAnim);
				
				FString str = FString::Printf(TEXT("당신의 차례가 아닙니다."));
				RenderMessage(FText::FromString(str));

				if (FailSound)
				{
					PlaySound(FailSound);
				}
			}

			return;
		}

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

			return;
		}

		//error 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Fail")));
	}
}

void UHUDDesk::FilTokenClicked()
{
}
