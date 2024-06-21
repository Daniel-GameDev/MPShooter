// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MPShooterPlayerState.h"

#include "Net/UnrealNetwork.h"

void AMPShooterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, DeathCount);
	DOREPLIFETIME(ThisClass, KillCount);
}
