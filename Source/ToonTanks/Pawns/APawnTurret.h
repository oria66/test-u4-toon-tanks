// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "APawnTurret.generated.h"

class AAPawnTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API AAPawnTurret : public APawnBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire", meta = (AllowPrivateAccess = "true"));
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire", meta = (AllowPrivateAccess = "true"));
	float FireRange = 500.0f;
	
	FTimerHandle FireTimerHandler;

	AAPawnTank *PawnTank;

	void CheckFireCondition();
	float DistanceToPawnTank();

public:
	AAPawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
