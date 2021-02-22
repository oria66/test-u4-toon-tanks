// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "HealthBar.generated.h"

//UCLASS(Abstract)
UCLASS()
class TOONTANKS_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthComponent(UHealthComponent *HealthComp){OwnerHealthComponent = HealthComp;}

protected:
    void NativeTick (const FGeometry & MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<UHealthComponent> OwnerHealthComponent;

	UPROPERTY( meta = (BindWidget))
	class UProgressBar *HealthBar;
	UPROPERTY( meta = (BindWidget))
	class UTextBlock *CurrentHealth;
	UPROPERTY( meta = (BindWidget))
	class UTextBlock *DefaultHealth;
};
