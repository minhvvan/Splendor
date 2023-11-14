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

		for (auto color : TEnumRange<ETokenColor>())
		{
			if (color == ETokenColor::E_End) break;

			int count = 4;
			if (color == ETokenColor::E_Pearl) count = 2;
			if (color == ETokenColor::E_Gold) count = 3;

			for (int i = 0; i < count; i++)
			{
				auto token = Cast<AToken>(world->SpawnActor<AActor>(TokenClass, loc, rotator, SpawnParams));

				if (token)
				{
					token->SetActorScale3D(FVector(0.35f));
					RemainTokens.Add(token);
					token->SetTokenType(color);
				}
			}
		}

		PlaceTokens(RemainTokens);
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
	if (bSelected)
	{
		SelectedTokens.Add(token);
	}
	else
	{
		SelectedTokens.Remove(token);
	}
}

void ATokenManager::PossessTokens(APlayerController* PC, bool bFirst)
{
	auto Player = Cast<APCPlay>(PC);
	auto PS = Player->GetPlayerState<APSPlayerInfo>();
	auto GS = GetWorld()->GetGameState<AGSPlay>();

	check(PS && GS && Player);

	FTokenCountList selected;
	selected.Init();

	bool flag = SelectedTokens.Num() == 3 ? true : false;
	int pearlCnt = 0;
	ETokenColor current = ETokenColor::E_End;
	for (auto token : SelectedTokens)
	{
		auto tType = token->GetTokenType();
		if (tType == ETokenColor::E_Pearl) pearlCnt++;

		if (current == ETokenColor::E_End)
		{
			current = tType;
		}
		else
		{
			if (current != tType) flag = false;
		}

		RemainTokens.Remove(token);
		GS->RemoveTokenIdx(token->GetIndex(), token->GetTokenType());

		selected[tType]++;

		token->Destroy();
	}

	PS->AddTokenByList(selected);

	if (flag || pearlCnt >= 2)
	{
		AddScroll.Broadcast(Player);
	}

	SelectedTokens.Reset();
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

