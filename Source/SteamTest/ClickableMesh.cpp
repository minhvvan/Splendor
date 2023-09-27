// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableMesh.h"
#include "Token.h"
#include "Components/AudioComponent.h"

UClickableMesh::UClickableMesh()
{
	bWantsInitializeComponent = true;
}

void UClickableMesh::InitializeComponent()
{
	Super::InitializeComponent();

	OnBeginCursorOver.AddDynamic(this, &UClickableMesh::HighlightOn);
	OnEndCursorOver.AddDynamic(this, &UClickableMesh::HighlightOff);
}

void UClickableMesh::HighlightOn(UPrimitiveComponent* TouchComp)
{
	auto AudioComp = Cast<AToken>(GetOwner())->GetAudio();

	if (AudioComp)
	{
		AudioComp->Play();
	}

	SetRenderCustomDepth(true);
}

void UClickableMesh::HighlightOff(UPrimitiveComponent* TouchComp)
{
	SetRenderCustomDepth(false);
}

void UClickableMesh::SetSelectedMat(bool bSelected)
{
	if (bSelected)
	{
		SetMaterial(2, SelectedMat);
	}
	else
	{
		SetMaterial(2, UnSelectedMat);
	}
}
