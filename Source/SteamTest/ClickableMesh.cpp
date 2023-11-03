// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableMesh.h"
#include "Token.h"
#include "Card.h"
#include "CardDummy.h"
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
	if (GetOwner()->IsA<AToken>())
	{
		auto AudioComp = Cast<AToken>(GetOwner())->GetAudio();

		if (AudioComp)
		{
			AudioComp->Play();
		}
	}
	else if (GetOwner()->IsA<ACard>())
	{
		auto AudioComp = Cast<ACard>(GetOwner())->GetAudio();

		if (AudioComp)
		{
			AudioComp->Play();
		}
	}
	else if (GetOwner()->IsA<ACardDummy>())
	{
		auto AudioComp = Cast<ACardDummy>(GetOwner())->GetAudio();

		if (AudioComp)
		{
			AudioComp->Play();
		}

		//dele
		OnHover.Broadcast();
	}

	SetRenderCustomDepth(true);
}

void UClickableMesh::HighlightOff(UPrimitiveComponent* TouchComp)
{
	SetRenderCustomDepth(false);
	OnLeave.Broadcast();
}

void UClickableMesh::SetSelectedMat(bool bSelected)
{
	if (bSelected)
	{
		if(SelectedMat && IsValid(SelectedMat)) SetMaterial(2, SelectedMat);
	}
	else
	{
		if (UnSelectedMat && IsValid(UnSelectedMat)) SetMaterial(2, UnSelectedMat);
	}
}
