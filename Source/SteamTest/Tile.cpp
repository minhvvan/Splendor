// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Token.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	if (Mesh)
	{
		Mesh->SetRelativeLocation(FVector(-210.0f, -450.0f, 0.0f));
		Mesh->SetWorldScale3D(FVector(0.5f));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetOnToken(class AToken* token)
{
	OnToken = token;
	if (OnToken)
	{
		token->OnSelected.AddDynamic(this, &ATile::OnSelected);
		token->OnUnSelected.AddDynamic(this, &ATile::OnUnSelected);
	}
}

void ATile::SetIsAble_Implementation(bool bAlbe)
{
	if (bAlbe)
	{
		Mesh->SetMaterial(0, UnSelectedMat);

		//click 가능하게
		if (OnToken)
		{
			OnToken->SetActorEnableCollision(true);
		}
	}
	else
	{
		if (Mesh)
		{
			Mesh->SetMaterial(0, DisabledMat);
		}

		//click 막기
		if (OnToken)
		{
			OnToken->SetActorEnableCollision(false);
		}
	}
}

void ATile::OnSelected_Implementation()
{
	if (Mesh)
	{
		Mesh->SetMaterial(0, SelectedMat);
	}
}

void ATile::OnUnSelected_Implementation()
{
	if (Mesh)
	{
		Mesh->SetMaterial(0, UnSelectedMat);
	}
}