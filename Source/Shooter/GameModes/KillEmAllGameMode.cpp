// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Shooter/AI/Controllers/ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    // If the killed pawn is the player, end the game with a loss
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
        return;
    }

    // If the killed pawn is an NPC, check if any more are alive. If so, game's not over yet
    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->IsDead())
        {
            return;
        }
    }

    EndGame(true);
    
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
