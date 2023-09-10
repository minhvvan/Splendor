// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSPlayerInfo.generated.h"

UCLASS()
class STEAMTEST_API APSPlayerInfo : public APlayerState
{
	GENERATED_BODY()
	
public:
	APSPlayerInfo();

	UFUNCTION()
	FString GetPName() const { return PName; };

	UFUNCTION()
	void SetPName(FString name) { PName = name; };

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void SetMyTrun(bool flag) { MyTurn = flag; };

	UFUNCTION()
	bool GetMyTurn() { return MyTurn; };

protected:
	UFUNCTION()
	void CopyProperties(class APlayerState* PlayerState) override;

	UFUNCTION()
	void OverrideWith(class APlayerState* PlayerState) override;

private:
	UPROPERTY(Replicated)
	FString PName;

	UPROPERTY(Replicated)
	bool MyTurn;
};
