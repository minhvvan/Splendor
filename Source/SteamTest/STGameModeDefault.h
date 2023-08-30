// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "STGameModeDefault.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API ASTGameModeDefault : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASTGameModeDefault();

	void BeginPlay();
};
