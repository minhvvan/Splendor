// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCost.h"
#include "Components/Border.h"
#include "PCPlay.h"
#include "CardData.h"
#include "GlobalEnum.h"

void UHUDCost::OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (CardData)
	{
		auto color = CardData->GetColor();

		//!TODO: color에 해당하는 토큰을 owner에게 넘기게 해야함 + 창닫기
		auto PC = Cast<APCPlay>(GetOwningPlayer());
		if (PC)
		{
			PC->TakeTokenFromOpp(color);
		}
	}
}

void UHUDCost::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BorderColor->OnMouseButtonDownEvent.BindUFunction(this, "OnClicked");
}
