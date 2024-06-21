// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerSlotWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MPSHOOTER_API UPlayerSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DeathsTextBlock;

public:
	FORCEINLINE void SetNameTextBlock(const FText InText) const { NameTextBlock->SetText(InText); }
	FORCEINLINE void SetKillsTextBlock(const FText InText) const { KillsTextBlock->SetText(InText); }
	FORCEINLINE void SetDeathsTextBlock(const FText InText) const { DeathsTextBlock->SetText(InText); }
	
};
