// Fill out your copyright notice in the Description page of Project Settings.


#include "Token.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AToken::AToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HoverSound"));
	AudioComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AToken::BeginPlay()
{
	Super::BeginPlay();
	
}

void AToken::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Mesh->OnBeginCursorOver.AddDynamic(this, &AToken::HighlightOn);
	Mesh->OnEndCursorOver.AddDynamic(this, &AToken::HighlightOff);

	if (AudioComponent->IsValidLowLevelFast())
	{
		AudioComponent->SetSound(HoverSound);
	}
}

// Called every frame
void AToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToken::HighlightOn(UPrimitiveComponent* TouchComp)
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
		AudioComponent->Play();
	}
}

void AToken::HighlightOff(UPrimitiveComponent* TouchComp)
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}