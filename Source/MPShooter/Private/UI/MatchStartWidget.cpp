// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MatchStartWidget.h"
#include "Components/Button.h"
#include "Core/MPShooterGameModeLobby.h"
#include "Kismet/GameplayStatics.h"

void UMatchStartWidget::StartButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Green,
		FString(TEXT("Listen Server started the match!"))
			);
	}

	if (AMPShooterGameModeLobby* MPShooterGameModeLobby = Cast<AMPShooterGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		MPShooterGameModeLobby->StartMatch();
		RemoveFromParent();
	}
}

void UMatchStartWidget::QuitButtonClicked()
{
}

bool UMatchStartWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ThisClass::StartButtonClicked);
	}
	if (QuitButton) // TODO: Quit to Lobby
	{
		QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
		QuitButton->SetIsEnabled(false); // remove
	}
	
	return true;
}
