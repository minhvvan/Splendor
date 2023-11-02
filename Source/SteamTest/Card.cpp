// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "HUDCard.h"
#include "CardManager.h"
#include "Components/WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UClickableMesh>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetIsReplicated(true);
	Mesh->SetWorldScale3D(FVector(1.0f, .75f, .2f));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("HoverSound"));
	AudioComp->SetupAttachment(Mesh);
	
	CardWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("CardWidgetComp"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CARD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Card.WBP_Card_C'"));
	if (CARD.Succeeded())
	{
		CardWidgetComp->SetWidgetClass(CARD.Class);
		CardWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CardWidgetComp->SetDrawSize(FVector2D(500.0f, 500.0f));
		CardWidgetComp->SetWorldRotation(FRotator(90.0f, 180.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACard::SetInfo(FCardInfo& info)
{
	//Widget  º¯°æ(score, bonus, cost, item, crown)
	if (CardWidgetComp && IsValid(CardWidgetComp))
	{
		Cast<UHUDCard>(CardWidgetComp->GetWidget())->SetInfo(info);
	}
}

