// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterCharacter.h"
#include "Shooter/Characters/ShooterCharacter.h"
#include "PlayerShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APlayerShooterCharacter : public AShooterCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	// Checks if the player is in combat
	UPROPERTY(VisibleAnywhere)
	bool bIsInCombat = false;

private:
	// Regen health on timer
	FTimerHandle RegainHealthTimer;
	UPROPERTY(EditAnywhere)
	float RegainHealthInterval = 1.f;
	void RegainHealth();
	
};
