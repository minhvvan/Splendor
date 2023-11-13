// Fill out your copyright notice in the Description page of Project Settings.


#include "Token.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AToken::AToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Mesh = CreateDefaultSubobject<UClickableMesh>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetIsReplicated(true);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("HoverSound"));
	AudioComp->SetupAttachment(Mesh);

	NetUpdateFrequency = 10;

	Index = 25;
}

// Called when the game starts or when spawned
void AToken::BeginPlay()
{
	Super::BeginPlay();
}

void AToken::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AToken::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AudioComp->IsValidLowLevelFast())
	{
		AudioComp->SetSound(HoverSound);
	}
}

void AToken::SetTokenType(ETokenColor color)
{
	TokenType = color;

	check(IsValid(Mesh));
	Mesh->SetStaticMesh(TokenMesh[color]);
}

// Called every frame
void AToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}