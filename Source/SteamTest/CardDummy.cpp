// Fill out your copyright notice in the Description page of Project Settings.


#include "CardDummy.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"
#include "HUDDummy.h"

// Sets default values
ACardDummy::ACardDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		NumWidgetComp->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ACardDummy::BeginPlay()
{
	Super::BeginPlay();
	
	if (Mesh && IsValid(Mesh))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Binding")));

		Mesh->OnHover.AddUObject(this, &ACardDummy::ShowNum);
		Mesh->OnLeave.AddUObject(this, &ACardDummy::hideNum);
	}
}

// Called every frame
void ACardDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardDummy::SetNum(int cardNum)
{
	if (IsValid(NumWidgetComp))
	{
		Cast<UHUDDummy>(NumWidgetComp->GetWidget())->SetRemainNum(cardNum);
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