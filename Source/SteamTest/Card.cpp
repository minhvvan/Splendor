// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "HUDCard.h"
#include "CardManager.h"
#include "Components/WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ClickableMesh.h"
#include "Net/UnrealNetwork.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

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
		CardWidgetComp->SetIsReplicated(true);
	}
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();

	//!TODO: 클라 위젯 업데이트 
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACard::SetInfo(FCardInfo& info)
{
	//Widget  변경(score, bonus, cost, item, crown)
	if (CardWidgetComp && IsValid(CardWidgetComp))
	{
		Cast<UHUDCard>(CardWidgetComp->GetWidget())->SetInfo(info);
	}
}

void ACard::ChangedCardInfo()
{
	//change
	//!TODO: 클라 위젯 업데이트 

}

void ACard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//!TODO: widget이 아니라 데이터를 replicate하고 onrep으로 업데이트
	DOREPLIFETIME(ACard, CardInfo);
}