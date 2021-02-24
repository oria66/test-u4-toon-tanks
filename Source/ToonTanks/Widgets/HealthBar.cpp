// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UHealthBar::NativeTick(const FGeometry & MyGeometry, float InDeltaTime) 
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if(!OwnerHealthComponent.IsValid())
        return;

    HealthBar->SetPercent(OwnerHealthComponent->GetCurrentHealth() / OwnerHealthComponent->GetDefaultHealth());

    FNumberFormattingOptions Opt;
    Opt.SetMaximumFractionalDigits(0);

    CurrentHealth->SetText(FText::AsNumber(OwnerHealthComponent->GetCurrentHealth(), &Opt));

    DefaultHealth->SetText(FText::AsNumber(OwnerHealthComponent->GetDefaultHealth(), &Opt));
}
