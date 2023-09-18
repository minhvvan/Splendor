// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "STGameModePlay.h"
#include "Tile.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("BeginPlay")));

	SpawnTiles();
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::SpawnTiles()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SpawnTiles")));

	//타일 생성
	auto GM = Cast<ASTGameModePlay>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		UWorld* world = GetWorld();
		for (int i = 0; i < 25; i++)
		{
			if (world)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector  SpawnLocation = GetActorLocation();

				world->SpawnActor<AActor>(TileClass, SpawnLocation, rotator, SpawnParams);
			}
		}
	}
}

