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
		// token �޾ƿͼ� ���� ���� �Ǵ�
		// �����ϸ� �޾ƿ���

		// �¿�: 1
		// ��밢: 4
		// �ϴ밢: 6

		auto Tokens = PC->GetSelectedTokens();

		Tokens.Sort([](const AToken& A, const AToken& B) {
			return A.GetIndex() < B.GetIndex();
		});

		for (auto token : Tokens)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%d"), token->GetIndex()));
		}

		//���� : 5
		bool flag = true;
		int prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex();
				continue;
			}

			if (token->GetIndex() != prev + 5)
			{
				flag = false;
				break;
			}

			prev = token->GetIndex();
		}

		if (flag) 
		{
			// Get
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UpDown")));

			return;
		}


		//�¿�: 1
		flag = true;
		prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex();
				continue;
			}

			if (token->GetIndex() != prev + 1)
			{
				flag = false;
				break;
			}

			prev = token->GetIndex();
		}

		if (flag)
		{
			// Get
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("LeftRIght")));

			return;
		}

		// ��밢: 4
		flag = true;
		prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex();
				continue;
			}

			if (token->GetIndex() != prev + 4)
			{
				flag = false;
				break;
			}

			prev = token->GetIndex();
		}

		if (flag)
		{
			// Get
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UpRight")));

			return;
		}

		//�ϴ밢: 6
		flag = true;
		prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex();
				continue;
			}

			if (token->GetIndex() != prev + 6)
			{
				flag = false;
				break;
			}

			prev = token->GetIndex();
		}

		if (flag)
		{
			// Get
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DownRight")));

			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Fail")));

	}
}

void UHUDDesk::FilTokenClicked()
{
}
