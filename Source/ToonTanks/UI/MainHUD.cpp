// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "ToonTanks/Widgets/MainHealthBar.h"
#include "ToonTanks/Pawns/APawnTank.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void AMainHUD::BeginPlay() 
{
    Super::BeginPlay();

    PlayerTank = Cast<AAPawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if(HealthBarClass)
    {
        HealthBar = CreateWidget<UMainHealthBar>(GetWorld(), HealthBarClass);

        if(HealthBar)
        {
            HealthBar->AddToViewport();
        }

        if(PlayerTank)
        {
            HealthBar->SetHealthComponent(PlayerTank->GetHealthComponent());
            //HealthBar->SetMainPlayer(PlayerTank);
        }
    }
}

void AMainHUD::DrawHUD() 
{
    Super::DrawHUD();
}
