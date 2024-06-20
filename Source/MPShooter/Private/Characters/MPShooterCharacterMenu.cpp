// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MPShooterCharacterMenu.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetInteractionComponent.h"

AMPShooterCharacterMenu::AMPShooterCharacterMenu()
	: Super()
{
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteractionComponent->SetupAttachment(GetFirstPersonCamera());
	WidgetInteractionComponent->bShowDebug = true;
}

void AMPShooterCharacterMenu::Activate(const FInputActionValue& Value)
{
	WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}
