// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHand.h"
#include "HUDHandCard.h"
#include "Components/Overlay.h"


void UHUDHand::NativeOnInitialized()
{
	//!------------Widget------------
	AnimSpeed = 10.f;
	CardAngle = 10.f;
	CardSpacing = 100.f;
	ArcHeight = 10.f;
	DefaultYOffset = 70.f;
	DefaultXOffset = 100.f;

	//!------------Interaction------------
	HoveredCardIdx = NONVALIDIDX;
	HoverYOffset = 220.f;
	HoverXOffset = 30.f;
}

void UHUDHand::AddCard(FCardInfo cardInfo)
{
	//card widget 생성 후 추가 + 위치 조정(함수)
	check(IsValid(CardClass));

	auto card = Cast<UHUDHandCard>(CreateWidget(GetWorld(), CardClass));
	//card info set
	card->SetInfo(cardInfo); 

	card->OnHover.AddUObject(this, &UHUDHand::OnHovered);
	card->OnLeave.AddUObject(this, &UHUDHand::OnLeaved);
	card->OnCardClicked.AddUObject(this, &UHUDHand::OnCardClicked);

	Hands.Add(card);
	OverlayHand->AddChild(card);

	UpdateCardPosition();
}


void UHUDHand::UpdateCardPosition()
{
	for (int i = 0 ; i < Hands.Num(); i++)
	{
		FWidgetTransform Transform = CalculatePosition(i);

		Hands[i]->StartRePostion(Transform, AnimSpeed);
	}
}

FWidgetTransform UHUDHand::CalculatePosition(int idx)
{
	FWidgetTransform NewPos;

	NewPos.Angle = CalculateAngle(idx);
	NewPos.Translation = FVector2D(CalculateXpos(idx), CalculateYpos(idx));

	return NewPos;
}

float UHUDHand::CalculateAngle(int idx)
{
	if (idx == HoveredCardIdx) return 0;

	float rot = ConvertIdx(idx);

	return rot * CardAngle;
}

float UHUDHand::CalculateXpos(int idx)
{
	auto WidgetSize = GetCachedGeometry().GetLocalSize();

	auto CenterX = WidgetSize.X / 2.f;
	int convertedIdx = ConvertIdx(idx);

	CenterX += (convertedIdx * CardSpacing) - DefaultXOffset + GetHoverXOffset(idx);
	return CenterX;
}

float UHUDHand::CalculateYpos(int idx)
{
	auto WidgetSize = GetCachedGeometry().GetLocalSize();

	auto CenterY = WidgetSize.Y / 2.f + DefaultYOffset - GetHoverYOffset(idx);
	int convertedIdx = ConvertIdx(idx);
	
	CenterY += abs(convertedIdx) * ArcHeight;
	return CenterY;
}

int UHUDHand::ConvertIdx(int idx)
{
	int total = Hands.Num();
	auto centerIdx = float(total - 1) / 2.f;

	auto temp = float(idx) - centerIdx;
	int result = temp;
	if (temp < 0)
	{
		result = FMath::RoundToPositiveInfinity(temp - .5f);
	}

	return result;
}

void UHUDHand::OnHovered(UHUDHandCard* HoverdCard)
{
	int idx = Hands.Find(HoverdCard);

	HoveredCardIdx = idx;
	UpdateCardPosition();
}

void UHUDHand::OnLeaved(UHUDHandCard* HoverdCard)
{
	HoveredCardIdx = NONVALIDIDX;
	UpdateCardPosition();
}

void UHUDHand::OnCardClicked(FCardInfo cardInfo)
{
	OnCard.Broadcast(cardInfo);
}


FORCEINLINE float UHUDHand::GetHoverYOffset(int idx)
{
	return idx == HoveredCardIdx ? HoverYOffset : 0;
}

float UHUDHand::GetHoverXOffset(int idx)
{
	if (HoveredCardIdx == NONVALIDIDX) return 0;

	if (idx == HoveredCardIdx) return 0;

	if (idx < HoveredCardIdx)
	{
		return -HoverXOffset;
	}
	else
	{
		return HoverXOffset;
	}
}

void UHUDHand::RemoveFromHands(int key)
{
	for (auto card : Hands)
	{
		if (card->GetInfo().key == key)
		{
			Hands.Remove(card);
			OverlayHand->RemoveChild(card);

			UpdateCardPosition();
			break;
		}
	}
}
