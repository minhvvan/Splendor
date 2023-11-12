// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "STGameModePlay.h"
#include "Kismet/GameplayStatics.h"
#include "GSPlay.h"
#include "Tile.h"
#include "Token.h"

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
		//1, 2, 3 모두
		Distance[i].SetNum(3);
	}

	{
		FillIdx.Emplace(12);
		FillIdx.Emplace(17);
		FillIdx.Emplace(16);
		FillIdx.Emplace(11);
		FillIdx.Emplace(6);
		FillIdx.Emplace(7);
		FillIdx.Emplace(8);
		FillIdx.Emplace(13);
		FillIdx.Emplace(18);
		FillIdx.Emplace(23);
		FillIdx.Emplace(22);
		FillIdx.Emplace(21);
		FillIdx.Emplace(20);
		FillIdx.Emplace(15);
		FillIdx.Emplace(10);
		FillIdx.Emplace(5);
		FillIdx.Emplace(0);
		FillIdx.Emplace(1);
		FillIdx.Emplace(2);
		FillIdx.Emplace(3);
		FillIdx.Emplace(4);
		FillIdx.Emplace(9);
		FillIdx.Emplace(14);
		FillIdx.Emplace(19);
		FillIdx.Emplace(24);
	}

	{
		TArray<int> d1 = { -6, -5, -4, -1, 1, 4, 5, 6 };
		TArray<int> d2 = { -12, -10, -8, -2, 2, 8, 10, 12 };

		for (int i = 0; i < 25; i++)
		{
			TArray<int> arr;
			for (int t = 0; t < 25; t++)
			{
				arr.Emplace(t);
			}

			for (int j = 0; j < 8; j++)
			{
				if (i % 5 == 0)
				{
					if (j==0 || j == 3 || j == 5) continue;
				}

				if (i % 5 == 4)
				{
					if (j == 2 || j == 4 || j == 7) continue;
				}

				int temp = i + d1[j];
				if (temp < 0 || temp >= 25) continue;

				arr.Remove(temp);
			}
			Distance[i][1] = arr;
		}

		for (int i = 0; i < 25; i++)
		{
			TArray<int> arr = Distance[i][1];

			for (int j = 0; j < 8; j++)
			{
				if (i % 5 == 0)
				{
					if (j == 0 || j == 3 || j == 5) continue;
				}

				if (i % 5 == 1)
				{
					if (j == 0 || j == 3 || j == 5) continue;
				}

				if (i % 5 == 3)
				{
					if (j == 2 || j == 4 || j == 7) continue;
				}

				if (i % 5 == 4)
				{
					if (j == 2 || j == 4 || j == 7) continue;
				}

				int temp = i + d2[j];
				if (temp < 0 || temp >= 25) continue;

				arr.Remove(temp);
			}
			Distance[i][2] = arr;
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

	int offset = 110;
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector loc = FVector(490, 520, 0);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				auto tile = Cast<ATile>(world->SpawnActor<AActor>(TileClass, loc, rotator, SpawnParams));
				if (tile)
				{
					tile->SetActorScale3D(FVector(0.55f));
					Tiles.Add(tile);
				}

				loc += FVector(0, offset, 0);
			}

			loc = FVector(490 - offset*(i+1), 520, 0);
		}
	}
}

void ATileManager::SetTokenLocs(TArray<AToken*>& Tokens)
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(GS);

	for (auto token : Tokens)
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			auto tile = Tiles[FillIdx[i]];
			//이미 있음
			if (tile->GetOnToken()) continue;

			token->SetIndex(FillIdx[i]);
			GS->AddTokenIdx(FillIdx[i], token->GetTokenType());
			token->SetActorLocation(tile->GetTokenLoc());
			tile->SetOnToken(token);

			break;  
		}
	}
}

void ATileManager::Clicked(int selectedIdx, int dist, bool bAble)
{
	if (bAble) SelectedTiles.Add(selectedIdx);
	else SelectedTiles.Remove(selectedIdx);

	UpdateBoardState();
}

void ATileManager::UpdateBoardState()
{
	int selectedNum = SelectedTiles.Num();

	if (selectedNum == 0)
	{
		for (auto tile : Tiles)
		{
			tile->SetIsAble(true);
		}
	}
	else if (selectedNum == 1)
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (SelectedTiles.Find(i) != INDEX_NONE) continue;
			if (Distance[SelectedTiles[0]][2].Find(i) != INDEX_NONE)
			{
				Tiles[i]->SetIsAble(false);
			}
			else
			{
				Tiles[i]->SetIsAble(true);
			}
		}
	}
	else if (selectedNum == 2)
	{
		//같은 라인만 
		SelectedTiles.Sort();
		int dir = abs(SelectedTiles[1] - SelectedTiles[0]);

		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (SelectedTiles.Find(i) != INDEX_NONE) continue;
			if (i == SelectedTiles[0] - dir || i == SelectedTiles[1] + dir)
			{
				if (dir == 1)
				{
					if (i / 5 != SelectedTiles[0] / 5)
					{
						Tiles[i]->SetIsAble(false);
						continue;
					}
				}
				else if (dir == 4)
				{
					if ((SelectedTiles[0] % 5 == 4 && i % 5 == 0) || (SelectedTiles[1] % 5 == 0 && i % 5 == 4))
					{
						Tiles[i]->SetIsAble(false);
						continue;
					}
				}
				else if(dir == 6)
				{
					if ((SelectedTiles[0] % 5 == 0 && i % 5 == 4) || (SelectedTiles[1] % 5 == 4 && i % 5 == 0))
					{
						Tiles[i]->SetIsAble(false);
						continue;
					}
				}

				Tiles[i]->SetIsAble(true);
			}
			else
			{
				Tiles[i]->SetIsAble(false);
			}
		}
	}
	else
	{
		//선택된 tile 아니면 모두 disable
		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (SelectedTiles.Find(i) != INDEX_NONE) continue;

			Tiles[i]->SetIsAble(false);
		}
	}
}

void ATileManager::ClearSeletedTiles()
{
	for (auto seleted : SelectedTiles)
	{
		Tiles[seleted]->SetOnToken(nullptr);
	}

	SelectedTiles.Reset();

	//모든 타일 정리
	UpdateBoardState();

	//!TODO: 가져간 타일을 끌지 말지 정해야함
}