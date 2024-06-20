// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MPShooterGameMode.h"
#include "MPShooterGameModeLobby.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterGameModeLobby : public AMPShooterGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
};
