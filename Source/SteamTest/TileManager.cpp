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

	Distance.SetNum(25);
	for (int i = 0; i < 25; i++)
	{
		Distance[i].SetNum(4);
	}

	{
		BoardIdx.Emplace(12);
		BoardIdx.Emplace(17);
		BoardIdx.Emplace(16);
		BoardIdx.Emplace(11);
		BoardIdx.Emplace(6);
		BoardIdx.Emplace(7);
		BoardIdx.Emplace(8);
		BoardIdx.Emplace(13);
		BoardIdx.Emplace(18);
		BoardIdx.Emplace(23);
		BoardIdx.Emplace(22);
		BoardIdx.Emplace(21);
		BoardIdx.Emplace(20);
		BoardIdx.Emplace(15);
		BoardIdx.Emplace(10);
		BoardIdx.Emplace(5);
		BoardIdx.Emplace(0);
		BoardIdx.Emplace(1);
		BoardIdx.Emplace(2);
		BoardIdx.Emplace(3);
		BoardIdx.Emplace(4);
		BoardIdx.Emplace(9);
		BoardIdx.Emplace(14);
		BoardIdx.Emplace(19);
		BoardIdx.Emplace(24);
	}

	{
		TArray<int> d1 = { -6, -5, -4, -1, 1, 4, 5, 6 };
		TArray<int> d2 = { -12, -10, -8, -2, 2, 8, 10, 12 };

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int temp = i + d1[j];
				if (temp < 0 || temp >= 25) continue;

				Distance[i][1].Emplace(temp);
			}
		}

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int temp = i + d2[j];
				if (temp < 0 || temp >= 25) continue;

				Distance[i][2].Emplace(temp);
			}
		}
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
				tile->SetBoardIdx(i);
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

TPair<TArray<FVector>, TArray<int>> ATileManager::GetTokenLocs(const TArray<class AToken*>& Tokens)
{
	TArray<FVector> Locs;
	TArray<int> Board;

	for (auto token : Tokens)
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			auto tile = Tiles[i];
			//이미 있음
			if (tile->GetOnToken()) continue;

			tile->SetOnToken(token);
			Locs.Add(tile->GetTokenLoc());
			Board.Add(BoardIdx[i]);

			break;  
		}
	}

	return { Locs, Board };
}

void ATileManager::Clicked(int boardIdx, int dist, bool bAble)
{
	//bAble: true -> 선택,  bAble: flase-> 해제
	if (bAble)
	{
		//선택 불가능한 곳 끄기
		SelectedTiles.Add(boardIdx);

		auto Disable = Distance[boardIdx][dist];
		for (auto DisableTile : Disable)
		{
			Tiles[DisableTile]->SetIsAble(false);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%d"), DisableTile));
		}
	}
	else
	{
		// 선택가능한 곳 다시 켜기
		SelectedTiles.Remove(boardIdx);

		for (auto SelectedTile : SelectedTiles)
		{
			auto Able = Distance[SelectedTile][dist];
			for (auto AbleTile : Able)
			{
				Tiles[AbleTile]->SetIsAble(true);
			}
		}
	}
}
