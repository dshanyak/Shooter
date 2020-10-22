// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooterCharacter.h"

void APlayerShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(RegainHealthTimer, this, &APlayerShooterCharacter::RegainHealth, RegainHealthInterval, true);
}

void APlayerShooterCharacter::RegainHealth()
{
    if(!bIsInCombat)
    {
        CurrentHealth = FMath::Clamp(CurrentHealth += 10.f, 0.f, MaxHealth);
    }
}

// Called to bind functionality to input
void APlayerShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Keybinds for keyboard AND gamepad
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveSideways"), this, &APlayerShooterCharacter::MoveSideways);
    PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacterBase::Shoot);

    // Keyboard keybindings
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookSideways"), this, &APawn::AddControllerYawInput);

    // Gamepad keybindings
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerShooterCharacter::LookUpRate);
    PlayerInputComponent->BindAxis(TEXT("LookSidewaysRate"), this, &APlayerShooterCharacter::LookSidewaysRate);

}

// Returns health as a percentage left of max health
float APlayerShooterCharacter::GetHealthPercent() const
{
    return CurrentHealth / MaxHealth;
}

void APlayerShooterCharacter::MoveForward(float AxisValue) 
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerShooterCharacter::MoveSideways(float AxisValue) 
{
    AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerShooterCharacter::LookUpRate(float AxisValue) 
{
    AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerShooterCharacter::LookSidewaysRate(float AxisValue) 
{
    AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}