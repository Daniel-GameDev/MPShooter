// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MPShooterGameModeLobby.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterGameModeLobby : public AGameMode
{
	GENERATED_BODY()

public:
	AMPShooterGameModeLobby();
	
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void StartMatch() override;

	AActor* FindSpawnZoneForPlayer();
	void RespawnPlayer(AController* Controller);

	UFUNCTION(Server, Reliable)
	void ServerRequestRespawn(AController* Controller);

	void DecreaseItemCount();
	
	int32 CurrentItemCount;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ItemClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 MaxItemsOnMap;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnInterval;

	FTimerHandle SpawnTimerHandle;

	void SpawnItems();

	UPROPERTY()
	TArray<TObjectPtr<AActor>> PlayerSpawnZones;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> ItemSpawnZones;
	
};
