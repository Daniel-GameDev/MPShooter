// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayersTableWidget.h"
#include "Components/ScrollBox.h"
#include "UI/PlayerSlotWidget.h"

void UPlayersTableWidget::AddPlayerToList(FString PlayerName, int32 Kills, int32 Deaths)
{
	if (PlayerSlotWidget && PlayerScrollBox)
	{
		if (UPlayerSlotWidget* NewPlayerSlotWidget = CreateWidget<UPlayerSlotWidget>(GetWorld(), PlayerSlotWidget))
		{
			NewPlayerSlotWidget->SetNameTextBlock(FText::FromString(PlayerName));
			NewPlayerSlotWidget->SetKillsTextBlock(FText::AsNumber(Kills));
			NewPlayerSlotWidget->SetDeathsTextBlock(FText::AsNumber(Deaths));
			PlayerScrollBox->AddChild(NewPlayerSlotWidget);
		}
	}
	
}

void UPlayersTableWidget::ClearPlayerList()
{
	if (PlayerScrollBox)
	{
		PlayerScrollBox->ClearChildren();
	}
}
