// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterCharacterBase.h"
#include "Engine/TargetPoint.h"
#include "Perception/PawnSensingComponent.h"

#include "NPCShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ANPCShooterCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()


public:
	// Constructor
	ANPCShooterCharacter();
	
	UPROPERTY(EditAnywhere)
	ATargetPoint* PatrolPoint;
	
	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensingComponent;

	// Adds dynamic to the PawnSensingComponent
	UFUNCTION()
	void CanSeePlayer(APawn* Pawn);
	
	UPROPERTY(EditDefaultsOnly)
	bool bCanSeePlayer = false;
};
