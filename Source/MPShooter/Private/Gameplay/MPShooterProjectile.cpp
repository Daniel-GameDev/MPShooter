// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MPShooterProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMPShooterProjectile::AMPShooterProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
	RootComponent = CollisionComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	bReplicates = true;
}

void AMPShooterProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		FMath::RandRange(MinDamage, MaxDamage),
		GetActorLocation(),
		DamageRadius,
		nullptr,
		IgnoreActors,
		this,
		GetInstigatorController(),
		true);
    
	Destroy();
}

void AMPShooterProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5.0f);
}

