// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MPShooterCharacter.h"
#include "MPShooterCharacterMenu.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterCharacterMenu : public AMPShooterCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteractionComponent;
	
public:
	AMPShooterCharacterMenu();
	
protected:
	virtual void Activate(const FInputActionValue& Value) override;
	
};
