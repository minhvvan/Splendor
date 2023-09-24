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

	OnClicked.AddDynamic(this, &UClickableMesh::OnClick);
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

void UClickableMesh::OnClick(UPrimitiveComponent* pComponent, FKey ButtonPressed)
{
	auto token = Cast<AToken>(GetOwner());

	if (token)
	{
		if (token->GetSelected())
		{
			token->SetSelected(false);

			SetMaterial(2, SelectedMat);
		}
		else
		{
			token->SetSelected(true);

			SetMaterial(2, UnSelectedMat);
		}
	}
}
