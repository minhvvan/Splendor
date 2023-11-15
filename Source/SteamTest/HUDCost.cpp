// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCost.h"
#include "Components/Border.h"
#include "PCPlay.h"
#include "CostData.h"
#include "GlobalEnum.h"

void UHUDCost::OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (CostData)
	{
		auto color = CostData->GetColor();

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
