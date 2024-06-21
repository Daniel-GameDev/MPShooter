// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MPSHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AmmoTextBlock;
	
public:
	FORCEINLINE void SetHealthTextBlock(int32 Health) const { HealthTextBlock->SetText(FText::AsNumber(Health)); }
	FORCEINLINE void SetAmmoTextBlock(int32 Ammo) const { AmmoTextBlock->SetText(FText::AsNumber(Ammo)); }
	
};
