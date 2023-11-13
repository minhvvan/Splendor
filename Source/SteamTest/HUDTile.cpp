// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTile.h"
#include "Components/Border.h"
#include "PCPlay.h"
#include "TileData.h"
#include "GlobalEnum.h"

void UHUDTile::OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	check(TileData);

	auto idx = TileData->GetIdx();

	auto PC = Cast<APCPlay>(GetOwningPlayer());
	if (PC)
	{
		//PC¿¡°Ô È¹µæ ¿äÃ»
		PC->GetTokenByIdx(idx);
	}
}

void UHUDTile::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BorderInner->OnMouseButtonDownEvent.BindUFunction(this, "OnClicked");
}
