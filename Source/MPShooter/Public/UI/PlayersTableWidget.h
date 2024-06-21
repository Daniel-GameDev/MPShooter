// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayersTableWidget.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API UPlayersTableWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> PlayerScrollBox;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Component)
	TSubclassOf<class UPlayerSlotWidget> PlayerSlotWidget;
	
public:
	void AddPlayerToList(FString PlayerName, int32 Kills, int32 Deaths);
	void ClearPlayerList();
	
};
