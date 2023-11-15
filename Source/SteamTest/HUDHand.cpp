// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHand.h"
#include "HUDHandCard.h"
#include "Components/Overlay.h"


void UHUDHand::NativeOnInitialized()
{
	AnimSpeed = 10.f;
}

void UHUDHand::AddCard(FCardInfo cardInfo)
{
	//card widget 생성 후 추가 + 위치 조정(함수)
	check(IsValid(CardClass));

	auto card = Cast<UHUDHandCard>(CreateWidget(GetWorld(), CardClass));
	//card info set
	card->SetInfo(cardInfo); 

	Hands.Add(card);
	OverlayHand->AddChild(card);

	UpdateCardPosition();
}


void UHUDHand::UpdateCardPosition()
{
	int iter = 0;

	for (auto card : Hands)
	{
		//!TODO: widget Pos 계산
		auto pos = FVector2D(iter++ * 100, 0);

		FWidgetTransform Transform;
		Transform.Translation = pos;

		card->StartRePostion(Transform, AnimSpeed);
	}
}
