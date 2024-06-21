// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnZone.generated.h"

UCLASS()
class MPSHOOTER_API AItemSpawnZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BoxComponent;
	
public:
	AItemSpawnZone();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	TSubclassOf<AActor> ItemClassToSpawn;
	
};
