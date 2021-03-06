// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainHealthBar;
class AAPawnTank;

UCLASS()
class TOONTANKS_API AMainHUD : public AHUD
{
	GENERATED_BODY()
			
public:
	//void SetHealthComponent(UHealthComponent *HealthComp){OwnerHealthComponent = HealthComp;}

	virtual void DrawHUD();

 	UPROPERTY(EditDefaultsOnly, Category = "Health")
  	TSubclassOf<UUserWidget> HealthBarClass;

protected:
	virtual void BeginPlay() override;

private:
  	UMainHealthBar* HealthBar;
	
	AAPawnTank *PlayerTank;
};
