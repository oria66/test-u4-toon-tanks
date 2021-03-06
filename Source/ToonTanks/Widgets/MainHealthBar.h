// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "MainHealthBar.generated.h"

UCLASS()
class TOONTANKS_API UMainHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthComponent(UHealthComponent *HealthComp){OwnerHealthComponent = HealthComp;}

protected:
    void NativeTick (const FGeometry & MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<UHealthComponent> OwnerHealthComponent;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UProgressBar *HealthBar;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock *CurrentHealth;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock *DefaultHealth;
};
