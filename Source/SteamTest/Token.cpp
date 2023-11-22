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

	bMoveComplete = true;
	LerpSpeed = 0.8f;
	PitchValue = 0.f;
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

	if (!bMoveComplete)
	{
		auto NewPos = InterpolatePos(DeltaTime);

		PitchValue = rand() % 3;
		FQuat QuatRotation = FQuat(InterpolateRot(DeltaTime));

		SetActorLocation(NewPos);
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		if (NewPos.Equals(Destination))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Destroy")));
			this->Destroy();
		}
	}
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

void AToken::MoveAndDestory(FVector dest)
{
	Destination = dest;
	bMoveComplete = false;
}

FVector AToken::InterpolatePos(float delta)
{
	FVector CurrentPos = GetActorLocation();

	auto NewPos = FMath::VInterpTo(CurrentPos, Destination, delta, LerpSpeed);

	return NewPos;
}

FRotator AToken::InterpolateRot(float delta)
{
	FRotator CurrentRot = GetActorRotation();

	FRotator DestRot = GetActorRotation();
	DestRot.Pitch += PitchValue;

	auto NewRot = FMath::RInterpTo(CurrentRot, DestRot, delta, .3f);

	return NewRot;
}
