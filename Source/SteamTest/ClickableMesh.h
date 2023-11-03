// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ClickableMesh.generated.h"

DECLARE_MULTICAST_DELEGATE(FDeleHover);
DECLARE_MULTICAST_DELEGATE(FDeleLeave);

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
	void SetSelectedMat(bool bSelected);

	FDeleHover OnHover;
	FDeleLeave OnLeave;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* UnSelectedMat;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* SelectedMat;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* DisabledMat;
};
