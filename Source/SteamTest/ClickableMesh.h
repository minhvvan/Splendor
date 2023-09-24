// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ClickableMesh.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UClickableMesh : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UClickableMesh();
	
protected:
	virtual void InitializeComponent() override;
	
public:
	UFUNCTION()
	void HighlightOn(UPrimitiveComponent* TouchComp);

	UFUNCTION()
	void HighlightOff(UPrimitiveComponent* TouchComp);

	UFUNCTION()
	void OnClick(UPrimitiveComponent* pComponent, FKey ButtonPressed);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* UnSelectedMat;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* SelectedMat;
};
