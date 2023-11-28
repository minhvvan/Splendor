// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalEnum.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "HUDCost.generated.h"

UCLASS()
class STEAMTEST_API UHUDCost : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnColor;	
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCost;

public:
	UFUNCTION()
	void OnClicked(/*const FGeometry& Geometry, const FPointerEvent& MouseEvent*/);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCostData* CostData;

protected:
	UPROPERTY(EditAnywhere)
	TMap<ETokenColor, UTexture2D*> TokenImg;

	virtual void NativeOnInitialized();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
