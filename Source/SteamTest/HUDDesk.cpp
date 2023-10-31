// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDesk.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUDCardHolder.h"
#include "HUDTokenHolder.h"
#include "HUDOverToken.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
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
	if (TxtScroll)
	{
		TxtScroll->SetText(FText::AsNumber(scroll));
	}
}

void UHUDDesk::SetTurnTxt(FString turn)
{
}

void UHUDDesk::BindState(APSPlayerInfo* ps)
{
	if (IsValid(ps))
	{
		CurrentState = ps;
		ps->OnScrollChanged.AddUObject(this, &UHUDDesk::ChangedScroll);
		ps->OnOverToken.AddUObject(this, &UHUDDesk::NotifyOverToken);
		ps->OnChangeToken.AddUObject(this, &UHUDDesk::ChangedToken);
	}
}

void UHUDDesk::ChangedScroll()
{
	if (CurrentState.IsValid())
	{
		SetScrollTxt(CurrentState->GetScroll());
	}
}

void UHUDDesk::ChangedToken()
{
	//!TODO: 클라는 동작 서버는 안됨
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("ChangedToken")));

	if (CurrentState.IsValid() && TokenHolder)
	{
		TokenHolder->UpdateTokenNum(CurrentState.Get());
	}
}

void UHUDDesk::RenderMessage(FString message)
{
	if (TxtMessage)
	{
		TxtMessage->SetText(FText::FromString(message));
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
			if (FailedGetAnim)
			{
				PlayAnimation(FailedGetAnim);
				
				RenderMessage(FString::Printf(TEXT("토큰을 선택해 주세요.")));

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
			auto PS = Cast<APSPlayerInfo>(PC->PlayerState);
			PC->SRPossessTokens(PS->GetBFirst());

			return;
		}
	}
}

void UHUDDesk::FilTokenClicked()
{
}

void UHUDDesk::NotifyOverToken()
{
	if (OverTokenClass)
	{
		auto widget = Cast<UHUDOverToken>(CreateWidget(GetWorld(), OverTokenClass));
		if (widget)
		{
			widget->AddToViewport();
		}
	}
}
