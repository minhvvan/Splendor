// Fill out your copyright notice in the Description page of Project Settings.


#include "TokenManager.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "Algo/RandomShuffle.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "GlobalStruct.h"
#include "GlobalEnum.h"

// Sets default values
ATokenManager::ATokenManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AToken> TOKEN(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_Token.BP_Token_C'"));
	if (TOKEN.Succeeded())
	{
		TokenClass = TOKEN.Class;
	}
}

// Called when the game starts or when spawned
void ATokenManager::BeginPlay()
{
	Super::BeginPlay();
	//RemainTokens.Init(nullptr, 25);
	
	SpawnTokens();
}

// Called every frame
void ATokenManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATokenManager::SpawnTokens()
{
	UWorld* world = GetWorld();
	auto GS = GetWorld()->GetGameState<AGSPlay>();

	check(IsValid(GS));

	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector loc = FVector(-210, -200, 0);

		auto CurrentTileState = GS->GetCurrentTileState();

		for (int i = 0; i < CurrentTileState.Num(); i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(TokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				token->SetTokenType(CurrentTileState[i]);
				token->SetIndex(i);
			}
		}

		//PlaceTokens(RemainTokens);
	}
}

void ATokenManager::SpawnTokensByList(FTokenCountList countList)
{
	UWorld* world = GetWorld();

	check(IsValid(world));
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
	FVector loc = FVector(-210, -200, 0);

	TArray<AToken*> Temp;
	for (auto count : countList)
	{
		for (int i = 0; i < count.Value; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(TokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				Temp.Add(token);
				token->SetTokenType(count.Key);
			}
		}
	}

	PlaceTokens(Temp);
}

void ATokenManager::PlaceTokens(TArray<AToken*>& Tokens)
{
	ASTGameModePlay* GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		//shuffle
		Algo::RandomShuffle(Tokens);

		GM->SetTokenSpawnLoc(Tokens);
	}
}

void ATokenManager::SelectedToken(AToken* token, bool bSelected)
{
	//if (bSelected)
	//{
	//	SelectedTokens.Add(token);
	//}
	//else
	//{
	//	SelectedTokens.Remove(token);
	//}
}

void ATokenManager::DestroyTokens(const TArray<FTokenIdxColor>& SelectedTokens)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("DestroyTokens")));

	bool bGold = false;
	for (auto selected : SelectedTokens)
	{
		if (selected.Color == ETokenColor::E_Gold) bGold = true;

		for (auto token : RemainTokens)
		{
			if (token->GetIndex() == selected.Idx)
			{
				RemainTokens.Remove(token);
				token->Destroy();
				break;
			}
		}
	}

	//Delegate
	if (bGold) 
	{
		OnGoldPossessed.Broadcast();
	}
}

void ATokenManager::GetTokenByIdx(APlayerController* PC, int idx)
{
	for (auto token : RemainTokens)
	{
		if (token->GetIndex() == idx)
		{
			auto PS = PC->GetPlayerState<APSPlayerInfo>();

			RemainTokens.Remove(token);

			token->Destroy();

			//ps update
			PS->AddToken(token->GetTokenType(), 1);
		}
	}
}