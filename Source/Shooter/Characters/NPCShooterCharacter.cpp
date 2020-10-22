// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCShooterCharacter.h"

#include "Shooter/AI/BTServices/BTService_PlayerLocationIfSeen.h"

ANPCShooterCharacter::ANPCShooterCharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &ANPCShooterCharacter::CanSeePlayer);
}

void ANPCShooterCharacter::CanSeePlayer(APawn* Pawn)
{
    bCanSeePlayer = true;

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Pawn->GetName());
}
