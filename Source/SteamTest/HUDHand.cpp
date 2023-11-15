// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHand.h"
#include "HUDCard.h"
#include "Components/Overlay.h"

void UHUDHand::AddCard(FCardInfo cardInfo)
{
	//card widget ���� �� �߰� + ��ġ ����(�Լ�)
	check(IsValid(CardClass));

	auto card = Cast<UHUDCard>(CreateWidget(GetWorld(), CardClass));
	//card info set
	card->SetInfo(cardInfo); 

	Hands.Add(card);
	OverlayHand->AddChild(card);
}