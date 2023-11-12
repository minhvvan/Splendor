// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalStruct.h"
#include "HUDTakeToken.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDTakeToken : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetTokens(TArray<FTokenCount> tokens);
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileToken;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCardData> TokenDataClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<ETokenColor, UTexture2D*> TokenTexture;
};
