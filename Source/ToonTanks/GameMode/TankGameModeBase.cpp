// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/APawnTank.h"
#include "ToonTanks/Pawns/APawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

ATankGameModeBase::ATankGameModeBase() 
{
    
}

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor *DeadActor) 
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if(AAPawnTurret *DestroyedTurret = Cast<AAPawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        TargetTurrets--;

        if(TargetTurrets == 0)
        {
            if(UGameplayStatics::GetCurrentLevelName(this, true) == FString(TEXT("Level2")))
            {
                HandleGameOver(true);
            }
            else
            {
                UGameplayStatics::OpenLevel(this, FName(TEXT("Level2")));
            }
        }        
    }
}

void ATankGameModeBase::HandleGameStart() 
{
    TargetTurrets = GetTargetTurrentCount();
    PlayerTank = Cast<AAPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    GameStart();

    if(PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnabledState(false);

       FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
        &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurrentCount() 
{
        TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}
