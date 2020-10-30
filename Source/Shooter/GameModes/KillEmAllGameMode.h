// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AKillEmAllGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION(BlueprintPure)
	int GetNumEnemies() const;

private:
	// handle ending the game
	void EndGame(bool bIsPlayerWinner) const;

	// disengage player from combat after an NPC death
	FTimerHandle DisengageFromCombatTimerHandle;
	UPROPERTY(EditAnywhere)
	float DisengageCombatDelay = 5.f;
	void DisengageCombat() const;

	// Number of enemies remaining
	UPROPERTY(EditDefaultsOnly)
	int EnemiesRemaining = 10;
	
	
};
