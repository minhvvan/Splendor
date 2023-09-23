// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "STGameModePlay.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ATile> TILE(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_Tile.BP_Tile_C'"));
	if (TILE.Succeeded())
	{
		TileClass = TILE.Class;
	}
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnTiles();
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::SpawnTiles()
{
	//타일 생성
	UWorld* world = GetWorld();

	int offset = 105;
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector loc = FVector(-210, -400, 0);
		int cnt = 0;
		int cursor = 3;
		int k = 1;
		int progress = 0;
		TArray<TPair<int, int>> Dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

		for (int i = 0; i < 25; i++)
		{
			auto tile = Cast<ATile>(world->SpawnActor<AActor>(TileClass, loc, rotator, SpawnParams));
			if (tile)
			{
				tile->SetActorScale3D(FVector(0.5f));
				Tiles.Add(tile);
			}

			cnt++;

			if (cnt == k)
			{
				//change dir
				cursor = (cursor + 1) % 4;
				cnt = 0;

				if (progress == 2)
				{
					k++;
					progress = 0;
				}
				progress++;
			}

			loc += FVector(offset * Dir[cursor].Key, offset * Dir[cursor].Value, 0);
		}
	}
}

TArray<FVector> ATileManager::GetTokenLocs(const TArray<class AToken*>& Tokens)
{
	TArray<FVector> Locs;

	for (auto token : Tokens)
	{
		for (auto tile : Tiles)
		{
			//이미 있음
			if (tile->GetOnToken()) continue;

			tile->SetOnToken(token);
			Locs.Add(tile->GetTokenLoc());
			break;
		}
	}

	return Locs;
}
