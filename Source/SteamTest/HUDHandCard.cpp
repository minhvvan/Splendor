// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHandCard.h"

void UHUDHandCard::StartRePostion(FWidgetTransform Pos, float Speed)
{
	DestPos = Pos;
	InterpolationSpeed = Speed;

	bCompletedMove = false;
}

void UHUDHandCard::Onclicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("hand clic")));
}

void UHUDHandCard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//flag∏¶ ≈Î«ÿ Hands Position update
	if (!bCompletedMove)
	{
		//update
		SetRenderTransform(IterpolateWidgetPos(InDeltaTime));
		
		//check
		bCompletedMove = IsCompletedMove();
	}
}

bool UHUDHandCard::IsCompletedMove()
{
	auto CurrentPos = GetRenderTransform();
	bool setted = GetCachedGeometry().GetLocalSize().X != 0 && GetCachedGeometry().GetLocalSize().Y != 0;

	return setted && DestPos.Translation == CurrentPos.Translation && DestPos.Angle == CurrentPos.Angle;
}

FWidgetTransform UHUDHandCard::IterpolateWidgetPos(float Delta)
{
	FWidgetTransform result;

	auto CurrentPos = GetRenderTransform();

	auto NewPos = FMath::Vector2DInterpTo(CurrentPos.Translation, DestPos.Translation, Delta, InterpolationSpeed);
	auto NewAngle = FMath::FInterpTo(CurrentPos.Angle, DestPos.Angle, Delta, InterpolationSpeed);

	result.Translation = NewPos;
	result.Angle = NewAngle;

	return result;
}
