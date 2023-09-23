// Fill out your copyright notice in the Description page of Project Settings.


#include "TokenManager.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "Algo/RandomShuffle.h"

// Sets default values
ATokenManager::ATokenManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AToken> RED(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_RedToken.BP_RedToken_C'"));
	if (RED.Succeeded())
	{
		RedTokenClass = RED.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> GREEN(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_GreenToken.BP_GreenToken_C'"));
	if (GREEN.Succeeded())
	{
		GreenTokenClass = GREEN.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> BLUE(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_BlueToken.BP_BlueToken_C'"));
	if (BLUE.Succeeded())
	{
		BlueTokenClass = BLUE.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> BLACK(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_BlackToken.BP_BlackToken_C'"));
	if (BLACK.Succeeded())
	{
		BlackTokenClass = BLACK.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> WHITE(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_WhiteToken.BP_WhiteToken_C'"));
	if (WHITE.Succeeded())
	{
		WhileTokenClass = WHITE.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> GOLD(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_GoldToken.BP_GoldToken_C'"));
	if (GOLD.Succeeded())
	{
		GoldTokenClass = GOLD.Class;
	}

	ConstructorHelpers::FClassFinder<AToken> PEARL(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_PearlToken.BP_PearlToken_C'"));
	if (PEARL.Succeeded())
	{
		PearlTokenClass = PEARL.Class;
	}
}

// Called when the game starts or when spawned
void ATokenManager::BeginPlay()
{
	Super::BeginPlay();
	
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

	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector loc = FVector(-210, -200, 0);

		//Red
		for (int i = 0; i < 4; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(RedTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);

				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Red: %d"), RemainTokens.Num()));
			}
		}

		//Green
		for (int i = 0; i < 4; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(GreenTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Green: %d"), RemainTokens.Num()));

			}
		}

		//Blue
		for (int i = 0; i < 4; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(BlueTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Blue: %d"), RemainTokens.Num()));

			}
		}

		//Black
		for (int i = 0; i < 4; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(BlackTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Black: %d"), RemainTokens.Num()));

			}
		}

		//White
		for (int i = 0; i < 4; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(WhileTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("White: %d"), RemainTokens.Num()));

			}
		}

		//Gold
		for (int i = 0; i < 3; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(GoldTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Gold: %d"), RemainTokens.Num()));

			}
		}

		//Pearl
		for (int i = 0; i < 2; i++)
		{
			auto token = Cast<AToken>(world->SpawnActor<AActor>(PearlTokenClass, loc, rotator, SpawnParams));

			if (token)
			{
				token->SetActorScale3D(FVector(0.35f));
				RemainTokens.Add(token);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Pearl: %d"), RemainTokens.Num()));

			}
		}

		PlaceTokens(RemainTokens);
	}
}

void ATokenManager::PlaceTokens(TArray<AToken*>& Tokens)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Tokens: %d"), Tokens.Num()));

	//GM���� Tilemanager spawnloc �޾Ƽ� ��ġ
	ASTGameModePlay* GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		//shuffle
		Algo::RandomShuffle(Tokens);

		auto SpawnLocs = GM->GetTokenSpawnLoc(Tokens);

		for (int i = 0; i < Tokens.Num(); i++)
		{
			Tokens[i]->SetActorLocation(SpawnLocs[i]);
		}
	}
}

void ATokenManager::FillTokens()
{
	PlaceTokens(UsedTokens);
}

void ATokenManager::GetTokens(TArray<AToken*>& Tokens, bool b1Player)
{
	if (b1Player)
	{
		for (auto token : Tokens)
		{
			RemainTokens.Remove(token);
			P1Tokens.Add(token);
		}
	}
	else
	{
		for (auto token : Tokens)
		{
			RemainTokens.Remove(token);
			P2Tokens.Add(token);
		}
	}
}

void ATokenManager::UseTokens(TArray<AToken*>& Tokens, bool b1Player)
{
}
