// Fill out your copyright notice in the Description page of Project Settings.


#include "PCMenu.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.h"
#include "HUDMultMenu.h"
#include "HUDServerRow.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ScrollBox.h"
#include "STGameModeLobby.h"


APCMenu::APCMenu()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MULT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_MultMenu.WBP_MultMenu_C'"));
	if (MULT.Succeeded())
	{
		MultMenuClass = MULT.Class;
	}
}

void APCMenu::ShowMultMenu()
{
	if (!WidgetMultMenu)
	{
		WidgetMultMenu = Cast<UHUDMultMenu>(CreateWidget(GetWorld(), MultMenuClass));
	}

	WidgetMultMenu->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void APCMenu::AddSessionRow(UHUDServerRow* row)
{
	if (WidgetMultMenu) WidgetMultMenu->AddSessionRow(row);
}

void APCMenu::FailedSearch()
{
	if (WidgetMultMenu) WidgetMultMenu->FailedSessionSearch();
}
