// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalEnum.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "HUDColorItem.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDColorItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetColor(ETokenColor color) { Color = color; };

	UFUNCTION(BlueprintCallable)
	ETokenColor GetColor() { return Color; };

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnColor;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgColor;

	UFUNCTION()
	void OnHoverd();
		
	UFUNCTION()
	void OnLeaved();

	UFUNCTION()
	void OnClicked();

private:
	UPROPERTY(EditAnywhere  )
	TMap<ETokenColor, UTexture2D*> TokenImg;

	UPROPERTY()
	ETokenColor Color;
};
