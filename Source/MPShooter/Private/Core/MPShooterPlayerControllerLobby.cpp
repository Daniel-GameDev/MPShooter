// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MPShooterPlayerControllerLobby.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Core/MPShooterPlayerState.h"
#include "MPShooter/MPShooterCharacter.h"
#include "UI/PlayerHUDWidget.h"
#include "UI/PlayersTableWidget.h"

void AMPShooterPlayerControllerLobby::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	
	if (AMPShooterCharacter* MPShooterCharacter = Cast<AMPShooterCharacter>(GetPawn()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MPShooterCharacter->GetInputMappinContext(), 0);
		}

		if (IsLocalController())
		{
			CreateCrosshair();
			ToggleCrosshairVisibility(true);
		}
	}
}

void AMPShooterPlayerControllerLobby::CreateCrosshair()
{
	if (CrossHair && !CrosshairInstance)
	{
		CrosshairInstance = CreateWidget<UUserWidget>(GetWorld(), CrossHair);
		if (CrosshairInstance)
		{
			CrosshairInstance->AddToViewport();
			ToggleCrosshairVisibility(true);
		}
	}
}

void AMPShooterPlayerControllerLobby::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		CreateCrosshair();
		ToggleCrosshairVisibility(true);

		PlayerHUDWidgetInstance = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (PlayerHUDWidgetInstance)
		{
			PlayerHUDWidgetInstance->AddToViewport();
		}

		UpdateHUDHealth(100);
		UpdateHUDAmmo(0); 
	}

	if (IsLocalController() && HasAuthority())
	{
		if (StartMatchWidgetClass)
		{
			StartMatchWidget = CreateWidget<UUserWidget>(this, StartMatchWidgetClass);
			if (StartMatchWidget)
			{
				StartMatchWidget->AddToViewport();
			}
		}
	}
}

void AMPShooterPlayerControllerLobby::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("TogglePlayersTable", IE_Pressed, this, &ThisClass::ShowPlayersTable);
	InputComponent->BindAction("TogglePlayersTable", IE_Released, this, &ThisClass::HidePlayersTable);
}

void AMPShooterPlayerControllerLobby::ServerRequestPlayerData_Implementation()
{
	TArray<FString> PlayerNames;
	TArray<int32> Kills;
	TArray<int32> Deaths;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->PlayerState)
		{
			if (AMPShooterPlayerState* MPShooterPlayerState = Cast<AMPShooterPlayerState>(PC->PlayerState))
			{
				PlayerNames.Add(MPShooterPlayerState->GetPlayerName());
				Kills.Add(MPShooterPlayerState->GetKills());
				Deaths.Add(MPShooterPlayerState->GetDeaths());
			}
		}
	}

	ClientReceivePlayerData(PlayerNames, Kills, Deaths);
}

void AMPShooterPlayerControllerLobby::ClientReceivePlayerData_Implementation(const TArray<FString>& PlayerNames,
	const TArray<int32>& Kills, const TArray<int32>& Deaths)
{
	if (PlayersTableWidget)
	{
		PlayersTableWidget->ClearPlayerList();
		for (int32 i = 0; i < PlayerNames.Num(); i++)
		{
			PlayersTableWidget->AddPlayerToList(PlayerNames[i], Kills[i], Deaths[i]);
		}
	}
}

void AMPShooterPlayerControllerLobby::ShowPlayersTable()
{
	if (!PlayersTableWidget && PlayersTableWidgetClass)
	{
		PlayersTableWidget = CreateWidget<UPlayersTableWidget>(this, PlayersTableWidgetClass);
	}

	if (PlayersTableWidget)
	{
		PlayersTableWidget->AddToViewport();
		ServerRequestPlayerData();
	}
}

void AMPShooterPlayerControllerLobby::HidePlayersTable()
{
	if (PlayersTableWidget)
	{
		PlayersTableWidget->RemoveFromParent();
	}
}

void AMPShooterPlayerControllerLobby::ToggleCrosshairVisibility(bool bVisible)
{
	if (CrosshairInstance)
	{
		CrosshairInstance->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void AMPShooterPlayerControllerLobby::UpdateHUDHealth(int32 NewHealth)
{
	if (PlayerHUDWidgetInstance)
	{
		PlayerHUDWidgetInstance->SetHealthTextBlock(NewHealth);
	}
}

void AMPShooterPlayerControllerLobby::UpdateHUDAmmo(int32 NewAmmo)
{
	if (PlayerHUDWidgetInstance)
	{
		PlayerHUDWidgetInstance->SetAmmoTextBlock(NewAmmo);
	}
}
