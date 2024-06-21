// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ItemSpawnZone.h"
#include "Components/BoxComponent.h"
#include "Core/MPShooterGameModeLobby.h"
#include "Kismet/KismetMathLibrary.h"

class AMPShooterGameModeLobby;

AItemSpawnZone::AItemSpawnZone()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxComponent);
}

void AItemSpawnZone::SpawnItem()
{
	if (ItemClassToSpawn)
	{
		FVector Origin = BoxComponent->GetComponentLocation();
		FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
		
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemClassToSpawn, RandomLocation, FRotator::ZeroRotator, SpawnParams);

		if (SpawnedItem)
		{
			if (AMPShooterGameModeLobby* MPShooterGameModeLobby = Cast<AMPShooterGameModeLobby>(GetWorld()->GetAuthGameMode()))
			{
				MPShooterGameModeLobby->CurrentItemCount++;
			}
		}
	}
}

