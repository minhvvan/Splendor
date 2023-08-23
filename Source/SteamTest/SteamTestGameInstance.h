// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SteamTestGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPlayerProfile: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;
};


UCLASS()
class STEAMTEST_API USteamTestGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USteamTestGameInstance();

	UFUNCTION()
	void ShowMainMenu();

	UFUNCTION()
	void ShowMultMenu();

	UFUNCTION()
	void StartSoloGame();

	UFUNCTION()
	void LoadGame();
	
	UFUNCTION()
	void SaveGame();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MultMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ServerRowClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDMainMenu* WidgetMainMenu;

	UPROPERTY(VisibleAnywhere)
	class UHUDMultMenu* WidgetMultMenu;

	FPlayerProfile* PlayerInfo;

	void MakePlayerInfo(FString name);

	void ChangeConnectionType();

	bool GetIsLanConnect() { return IsLanConnection ? true : false; };

	void CreateSession();
	void FindSession();
	void JoinSession(int32 idx);

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	FString PlayerProfileSlot = "PlayerProfileSlot";

	bool IsLanConnection;

	IOnlineSessionPtr OnlineSessionInterface;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
