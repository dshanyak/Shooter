// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooterCharacter.h"

void APlayerShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    // GetWorldTimerManager().SetTimer(RegainHealthTimer, this, &APlayerShooterCharacter::RegainHealth, RegainHealthInterval, true);
}

void APlayerShooterCharacter::RegainHealth()
{
    if(!bIsInCombat)
    {
        CurrentHealth = FMath::Clamp(CurrentHealth += 10.f, 0.f, MaxHealth);
        UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHealth);
    }
}
