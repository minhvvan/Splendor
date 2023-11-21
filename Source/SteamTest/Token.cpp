// Fill out your copyright notice in the Description page of Project Settings.


#include "Token.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"
#include "Net/UnrealNetwork.h"
#include "STGameModePlay.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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
	Mesh->OnBeginCursorOver.AddDynamic(this, &AToken::OnHover);
	Mesh->OnEndCursorOver.AddDynamic(this, &AToken::OnLeave);
}

void AToken::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AToken, Index);
	DOREPLIFETIME(AToken, TokenType);
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

void AToken::OnHover(UPrimitiveComponent* Target)
{
	check(IsValid(Mesh) && IsValid(AudioComp));

	Mesh->SetRenderCustomDepth(true);
	AudioComp->Play();
}

void AToken::OnLeave(UPrimitiveComponent* Target)
{
	Mesh->SetRenderCustomDepth(false);
}