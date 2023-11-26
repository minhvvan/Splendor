// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDColorItem.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ListViewBase.h"
#include "HUDAnyColor.h"
#include "CostData.h"

void UHUDColorItem::NativeOnInitialized()
{
	BtnColor->OnHovered.AddDynamic(this, &UHUDColorItem::OnHoverd);
	BtnColor->OnUnhovered.AddDynamic(this, &UHUDColorItem::OnLeaved);
	BtnColor->OnClicked.AddDynamic(this, &UHUDColorItem::OnClicked);
}

void UHUDColorItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto Data = Cast<UCostData>(ListItemObject);
	if (Data)
	{
		auto color = Data->GetColor();
		ImgColor->SetBrushFromTexture(TokenImg[color]);
	}
}

void UHUDColorItem::OnHoverd()
{

}

void UHUDColorItem::OnLeaved()
{

}

void UHUDColorItem::OnClicked()
{
	//Parent ¸øÃ£À½
	auto OwnList = GetOwningListView();
	auto Parent = OwnList->GetParent();
	auto Outer1 = Parent->GetOuter();
	auto Outer2 = Outer1->GetOuter();

	auto AnyColor = Cast<UHUDAnyColor>(Outer2);
	AnyColor->CallUpdate(Color);
}
