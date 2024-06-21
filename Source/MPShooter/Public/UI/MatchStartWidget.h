// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchStartWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class MPSHOOTER_API UMatchStartWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

protected:
	virtual bool Initialize() override;
	
};
