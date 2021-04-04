// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHealthBar.h"
#include "ToonTanks/Pawns/APawnTank.h"
#include "Kismet/GameplayStatics.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UMainHealthBar::NativeTick(const FGeometry & MyGeometry, float InDeltaTime) 
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if(!OwnerHealthComponent.IsValid())
        return;

    AAPawnTank *PlayerTank = Cast<AAPawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if(!PlayerTank)
        return;

    HealthBar->SetPercent(OwnerHealthComponent->GetCurrentHealth() / OwnerHealthComponent->GetDefaultHealth());

    FNumberFormattingOptions Opt;
    Opt.SetMaximumFractionalDigits(0);

    CurrentHealth->SetText(FText::AsNumber(OwnerHealthComponent->GetCurrentHealth(), &Opt));

    DefaultHealth->SetText(FText::AsNumber(OwnerHealthComponent->GetDefaultHealth(), &Opt));

    AmmoCounter->SetText(FText::AsNumber(PlayerTank->GetAmmo(), &Opt));
}
