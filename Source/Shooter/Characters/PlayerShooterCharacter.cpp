// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooterCharacter.h"

// Called at the beginning of play
void APlayerShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set up timer to regenerate health based every loop
    GetWorldTimerManager().SetTimer(RegainHealthTimer, this, &APlayerShooterCharacter::RegainHealth, RegainHealthInterval, true);
}

// Constructor
APlayerShooterCharacter::APlayerShooterCharacter()
{
    // Set up noise emitter
    NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
}

// Regenerate health every loop if the player is not in combat
void APlayerShooterCharacter::RegainHealth()
{
    if(!bIsInCombat)
    {
        CurrentHealth = FMath::Clamp(CurrentHealth += 10.f, 0.f, MaxHealth); // Health is limited to be between max health and 0
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

// Called every frame
void APlayerShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Replicates how the NPCs would hear footsteps behind them
    // Note* Didn't actually add a noise, this is only for AI awareness
    MakeNoise(1.f, this);
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