// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SpawnZone.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ASpawnZone::ASpawnZone(const FObjectInitializer& ObjectInitializer)
	:APlayerStart(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(GetCapsuleComponent());
	BoxComponent->SetBoxExtent(FVector(100.f));
	BoxComponent->SetHiddenInGame(false);
	BoxComponent->ShapeColor = FColor::Green;
}
