// Fill out your copyright notice in the Description page of Project Settings.

#include "APawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "APawnTank.h"
#include "Components/WidgetComponent.h"
#include "ToonTanks/Widgets/HealthBar.h"

AAPawnTurret::AAPawnTurret() 
{
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AAPawnTurret::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(!PawnTank || DistanceToPawnTank() > FireRange)
    {
        return;
    }

    RotateTurret(PawnTank->GetActorLocation());
}

void AAPawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

void AAPawnTurret::BeginPlay() 
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireTimerHandler,
                                            this,
                                            &AAPawnTurret::CheckFireCondition,
                                            FireRate,
                                            true);

    PawnTank = Cast<AAPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    if(HealthWidgetComp)
    {
        UHealthBar *HealthBar = Cast<UHealthBar>(HealthWidgetComp->GetUserWidgetObject());
        HealthBar->SetHealthComponent(HealthComponent);
  }
}

void AAPawnTurret::CheckFireCondition() 
{
    if(!PawnTank)
        return;

    if(!PawnTank->GetIsPlayerAlive())
    {
        return;
    }

    if(DistanceToPawnTank() <= FireRange)
    {
        Fire();
    }
}

float AAPawnTurret::DistanceToPawnTank() 
{
    if(!PawnTank)
        return 0.0f;

    return FVector::Dist(PawnTank->GetActorLocation(), GetActorLocation());
}
