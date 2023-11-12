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

		//!TODO: color�� �ش��ϴ� ��ū�� owner���� �ѱ�� �ؾ��� + â�ݱ�
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
