// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MPShooterGameModeLobby.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay/ItemSpawnZone.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AMPShooterGameModeLobby::AMPShooterGameModeLobby()
{
	PrimaryActorTick.bCanEverTick = false;
	bDelayedStart = true;
	MaxItemsOnMap = 30;
	SpawnInterval = 5.0f;
	CurrentItemCount = 0;
}

void AMPShooterGameModeLobby::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerSpawnZones);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnZone::StaticClass(), ItemSpawnZones);
}

void AMPShooterGameModeLobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers)
				);

			if (APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
		}
	}
}

void AMPShooterGameModeLobby::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if(GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers - 1)
				);

			if (APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s has exited the game!"), *PlayerName)
				);
			}
		}
	}
}

void AMPShooterGameModeLobby::StartMatch()
{
	Super::StartMatch();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMPShooterGameModeLobby::SpawnItems, SpawnInterval, true);
}

AActor* AMPShooterGameModeLobby::FindSpawnZoneForPlayer()
{
	for (AActor* SpawnZone : PlayerSpawnZones)
	{
		TArray<AActor*> OverlappingActors;
		SpawnZone->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

		if (OverlappingActors.Num() == 0)
		{
			return SpawnZone;
		}
	}
	
	return nullptr;
}

void AMPShooterGameModeLobby::RespawnPlayer(AController* Controller)
{
	if (Controller)
	{
		if (AActor* SpawnZone = FindSpawnZoneForPlayer())
		{
			RestartPlayerAtPlayerStart(Controller, SpawnZone);
		}
		else
		{
			FTimerHandle RespawnTimerHandle;
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, FTimerDelegate::CreateUObject(this, &ThisClass::RespawnPlayer, Controller), 5.0f, false);
		}
	}
}

void AMPShooterGameModeLobby::DecreaseItemCount()
{
	CurrentItemCount--;

	if (CurrentItemCount < MaxItemsOnMap)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMPShooterGameModeLobby::SpawnItems, SpawnInterval, true);
		}
	}
}

void AMPShooterGameModeLobby::SpawnItems()
{
	if (CurrentItemCount >= MaxItemsOnMap)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	for (AActor* SpawnZone : ItemSpawnZones)
	{
		if (AItemSpawnZone* ItemSpawnZone = Cast<AItemSpawnZone>(SpawnZone))
		{
			ItemSpawnZone->SpawnItem();
			CurrentItemCount++;
		}

		if (CurrentItemCount >= MaxItemsOnMap)
		{
			break;
		}
	}
}

void AMPShooterGameModeLobby::ServerRequestRespawn_Implementation(AController* Controller)
{
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, FTimerDelegate::CreateUObject(this, &ThisClass::RespawnPlayer, Controller), 5.0f, false);
}
