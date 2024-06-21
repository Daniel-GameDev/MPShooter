// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Ammo.h"
#include "Characters/MPShooterCharacterLobby.h"
#include "Components/SphereComponent.h"


AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = SphereComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->CastShadow = false;
	StaticMesh->SetupAttachment(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	
	bReplicates = true;
}

void AAmmo::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMPShooterCharacterLobby* MPShooterCharacterLobby = Cast<AMPShooterCharacterLobby>(OtherActor))
	{
		MPShooterCharacterLobby->PickUpAmmo(this);
	}
}

