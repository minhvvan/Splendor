// Fill out your copyright notice in the Description page of Project Settings.


#include "CardDummy.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"
#include "HUDDummy.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACardDummy::ACardDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Mesh = CreateDefaultSubobject<UClickableMesh>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetIsReplicated(true);
	Mesh->SetWorldScale3D(FVector(1.0f, .75f, .2f));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("HoverSound"));
	AudioComp->SetupAttachment(Mesh);

	NumWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("NumWidgetComp"));
	static ConstructorHelpers::FClassFinder<UUserWidget> DUMMY(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_RemainCard.WBP_RemainCard_C'"));
	if (DUMMY.Succeeded())
	{
		NumWidgetComp->SetWidgetClass(DUMMY.Class);
		NumWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		NumWidgetComp->SetDrawSize(FVector2D(500.0f, 500.0f));
		NumWidgetComp->SetWorldRotation(FRotator(90.0f, 180.0f, 0.0f));
		NumWidgetComp->SetIsReplicated(true);
		NumWidgetComp->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ACardDummy::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh && IsValid(Mesh))
	{
		Mesh->OnHover.AddUObject(this, &ACardDummy::ShowNum);
		Mesh->OnLeave.AddUObject(this, &ACardDummy::hideNum);
	}

	bInitialized = true;
	Cast<UHUDDummy>(NumWidgetComp->GetWidget())->SetRemainNumText(RemainCardNum);
}

void ACardDummy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACardDummy, RemainCardNum);
}

// Called every frame
void ACardDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardDummy::SetNum(int cardNum)
{
	if (RemainCardNum != cardNum)
	{
		RemainCardNum = cardNum;
		if (IsValid(NumWidgetComp))
		{
			Cast<UHUDDummy>(NumWidgetComp->GetWidget())->SetRemainNumText(RemainCardNum);
		}
	}
}

void ACardDummy::AddNum(int num)
{
	RemainCardNum += num;
	if (IsValid(NumWidgetComp))
	{
		Cast<UHUDDummy>(NumWidgetComp->GetWidget())->SetRemainNumText(RemainCardNum);
	}
}

void ACardDummy::ShowNum()
{
	if (IsValid(NumWidgetComp))
	{
		NumWidgetComp->SetVisibility(true);
	}
}

void ACardDummy::hideNum()
{
	if (IsValid(NumWidgetComp))
	{
		NumWidgetComp->SetVisibility(false);
	}
}

void ACardDummy::OnRep_RemainCardNum()
{
	if (bInitialized && IsValid(NumWidgetComp))
	{
		Cast<UHUDDummy>(NumWidgetComp->GetWidget())->SetRemainNumText(RemainCardNum);
	}
}