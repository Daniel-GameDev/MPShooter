// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MPShooterCharacterLobby.h"
#include "Blueprint/UserWidget.h"
#include "Core/MPShooterGameModeLobby.h"
#include "Core/MPShooterPlayerControllerLobby.h"
#include "Gameplay/MPShooterProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AMPShooterCharacterLobby::Activate(const FInputActionValue& Value)
{
	if (Ammo > 0)
	{
		if (HasAuthority())
		{
			ServerFire();
		}
		else
		{
			ShootProjectile();
		}
	}

	//Uncomment to test death
	//HandleDeath();
	//
}

void AMPShooterCharacterLobby::ServerRespawn_Implementation()
{
	Respawn();
}

void AMPShooterCharacterLobby::Respawn()
{
	if (AController* ThisController = GetController())
	{
		if (AMPShooterGameModeLobby* MPShooterGameModeLobby = Cast<AMPShooterGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			MPShooterGameModeLobby->ServerRequestRespawn(ThisController);
		}
	}
	
	SetLifeSpan(0.1f);
}

void AMPShooterCharacterLobby::HandleDeath()
{
	if (AMPShooterPlayerControllerLobby* MPShooterPlayerControllerLobby = Cast<AMPShooterPlayerControllerLobby>(GetController()))
	{
		MPShooterPlayerControllerLobby->ToggleCrosshairVisibility(true);
	}
	
	if (HasAuthority())
	{
		Respawn();
	}
	else
	{
		ServerRespawn();
	}
}

void AMPShooterCharacterLobby::OnItemPickedUp()
{
	if (HasAuthority())
	{
		if (AMPShooterGameModeLobby* GameMode = Cast<AMPShooterGameModeLobby>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->DecreaseItemCount();
		}
	}
	else
	{
		ServerOnItemPickedUp();
	}
}

AMPShooterCharacterLobby::AMPShooterCharacterLobby()
{
	Ammo = 0;
	Health = 100;
}

void AMPShooterCharacterLobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME_CONDITION(AMPShooterCharacterLobby, Health, COND_OwnerOnly);
	// DOREPLIFETIME_CONDITION(AMPShooterCharacterLobby, Ammo, COND_OwnerOnly);
	DOREPLIFETIME(AMPShooterCharacterLobby, Health);
	DOREPLIFETIME(AMPShooterCharacterLobby, Ammo);
}

void AMPShooterCharacterLobby::ServerFire_Implementation()
{
	if (Ammo > 0)
	{
		ShootProjectile();
	}
}

void AMPShooterCharacterLobby::ShootProjectile()
{
	if (ProjectileClass && GetController())
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FVector ShootDirection = CameraRotation.Vector();
		if (AMPShooterProjectile* MPShooterProjectile = GetWorld()->SpawnActor<AMPShooterProjectile>(ProjectileClass, CameraLocation, ShootDirection.Rotation(), SpawnParams))
		{
			Ammo--;

			if (AMPShooterPlayerControllerLobby* PC = Cast<AMPShooterPlayerControllerLobby>(GetController()))
			{
				PC->UpdateHUDAmmo(Ammo);
			}
		}
	}
}

void AMPShooterCharacterLobby::PickUpAmmo(AActor* AmmoActor)
{
	if (HasAuthority())
	{
		Ammo += 1;
		AmmoActor->Destroy();
		OnItemPickedUp();
		if (AMPShooterPlayerControllerLobby* PC = Cast<AMPShooterPlayerControllerLobby>(GetController()))
		{
			PC->UpdateHUDAmmo(Ammo);
		}
	}
	else
	{
		ServerPickUpAmmo(AmmoActor);
	}
}

void AMPShooterCharacterLobby::OnRep_Health()
{
	if (AMPShooterPlayerControllerLobby* PC = Cast<AMPShooterPlayerControllerLobby>(GetController()))
	{
		PC->UpdateHUDHealth(Health);
	}
}

void AMPShooterCharacterLobby::OnRep_Ammo()
{
	UpdateAmmoHUD();
}

void AMPShooterCharacterLobby::UpdateAmmoHUD()
{
	if (AMPShooterPlayerControllerLobby* PC = Cast<AMPShooterPlayerControllerLobby>(GetController()))
	{
		PC->UpdateHUDAmmo(Ammo);
	}
}

void AMPShooterCharacterLobby::ServerPickUpAmmo_Implementation(AActor* AmmoActor)
{
	PickUpAmmo(AmmoActor);
}

void AMPShooterCharacterLobby::ServerOnItemPickedUp_Implementation()
{
	OnItemPickedUp();
}
