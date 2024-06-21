// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MPShooterCharacter.h"
#include "MPShooterCharacterLobby.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterCharacterLobby : public AMPShooterCharacter
{
	GENERATED_BODY()

protected:
	virtual void Activate(const FInputActionValue& Value) override;
	
	UFUNCTION(Server, Reliable)
	void ServerRespawn();
	
	void Respawn();
	void HandleDeath();
	void OnItemPickedUp();

	UPROPERTY(ReplicatedUsing = OnRep_Health)
	int32 Health;

	UPROPERTY(ReplicatedUsing = OnRep_Ammo)
	int32 Ammo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AMPShooterProjectile> ProjectileClass;

public:
	AMPShooterCharacterLobby();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void ServerOnItemPickedUp();

	UFUNCTION(Server, Reliable)
	void ServerPickUpAmmo(AActor* AmmoActor);

	UFUNCTION(Server, Reliable)
	void ServerFire();

	void ShootProjectile();

	void PickUpAmmo(AActor* AmmoActor);

	UFUNCTION()
	void OnRep_Health();
	
	UFUNCTION()
	void OnRep_Ammo();

private:
	void UpdateAmmoHUD();
	
};
