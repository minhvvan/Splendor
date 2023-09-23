// Fill out your copyright notice in the Description page of Project Settings.


#include "Token.h"

// Sets default values
AToken::AToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AToken::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

