// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GlobalEnum.h"
#include "HUDTile.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDTile : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnToken;

public:
	UFUNCTION()
	void OnClicked();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UTileData* TileData;

protected:
	UPROPERTY(EditAnywhere)
	TMap<ETokenColor, UTexture2D*> TokenImg;

	virtual void NativeOnInitialized();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
