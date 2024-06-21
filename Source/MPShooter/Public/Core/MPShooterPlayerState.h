// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MPShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int32 DeathCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int32 KillCount;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	FORCEINLINE int32 GetKills() const {return KillCount;}
	FORCEINLINE int32 GetDeaths() const {return DeathCount;}
	
};
