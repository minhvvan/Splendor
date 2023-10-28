// Fill out your copyright notice in the Description page of Project Settings.


#include "TokenManager.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"
#include "Algo/RandomShuffle.h"
#include "PSPlayerInfo.h"

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
				token->SetTokenType(ETokenType::T_Red);
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
				token->SetTokenType(ETokenType::T_Green);
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
				token->SetTokenType(ETokenType::T_Blue);
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
				token->SetTokenType(ETokenType::T_Black);
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
				token->SetTokenType(ETokenType::T_White);
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
				token->SetTokenType(ETokenType::T_Gold);
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
				token->SetTokenType(ETokenType::T_Pearl);
			}
		}

		PlaceTokens(RemainTokens);
	}
}

void ATokenManager::PlaceTokens(TArray<AToken*>& Tokens)
{
	//GM에게 Tilemanager spawnloc 받아서 위치
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
	if (bSelected)
	{
		SelectedTokens.Add(token);
	}
	else
	{
		SelectedTokens.Remove(token);
	}
}

void ATokenManager::FillTokens()
{
	PlaceTokens(UsedTokens);
}

void ATokenManager::PossessTokens(APlayerController* PC)
{
	auto Player = Cast<APCPlay>(PC);
	if (Player)
	{
		bool b1Player = Player->GetTurn();

		for (auto token : SelectedTokens)
		{
			RemainTokens.Remove(token);
			if (b1Player) P1Tokens.Add(token);
			else P2Tokens.Add(token);

			auto PS = Player->GetPlayerState<APSPlayerInfo>();
			if (PS)
			{
				PS->AddToken(token->GetTokenType());
			}

			token->SetActorLocation(FVector(-300, 0, 0));
		}

		if (b1Player)
		{
			//~Test
			if (P1Tokens.Num() > 10)
			{
				Player->PopUpOverToken();
			}
		}
		else
		{
			//~Test
			if (P2Tokens.Num() > 10)
			{
				Player->PopUpOverToken();
			}
		}

		SelectedTokens.Reset();
	}
}

void ATokenManager::UseTokens(TArray<AToken*>& Tokens, bool b1Player)
{
}