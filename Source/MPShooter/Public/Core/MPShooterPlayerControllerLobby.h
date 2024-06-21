// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPShooterPlayerControllerLobby.generated.h"

class UPlayersTableWidget;

/**
 * 
 */
UCLASS()
class MPSHOOTER_API AMPShooterPlayerControllerLobby : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> StartMatchWidget;

	UPROPERTY()
	TObjectPtr<UPlayersTableWidget> PlayersTableWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> CrosshairInstance;

	UPROPERTY()
	TObjectPtr<class UPlayerHUDWidget> PlayerHUDWidgetInstance;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UUserWidget> StartMatchWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UPlayersTableWidget> PlayersTableWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UUserWidget> CrossHair;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	
	virtual void OnPossess(APawn* aPawn) override;

	// UFUNCTION(Client, Reliable)
	void CreateCrosshair();
	
public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION(Server, Reliable)
	void ServerRequestPlayerData();
	
	UFUNCTION(Client, Reliable)
	void ClientReceivePlayerData(const TArray<FString>& PlayerNames, const TArray<int32>& Kills, const TArray<int32>& Deaths);
	
	void ShowPlayersTable();
	void HidePlayersTable();

	void ToggleCrosshairVisibility(bool bVisible);

	void UpdateHUDHealth(int32 NewHealth);
	void UpdateHUDAmmo(int32 NewAmmo);
	
};
