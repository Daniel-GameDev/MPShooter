// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "SpawnZone.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class MPSHOOTER_API ASpawnZone : public APlayerStart
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	
public:
	ASpawnZone(const FObjectInitializer& ObjectInitializer);
	
};
