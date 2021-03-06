// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "APawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API AAPawnTank : public APawnBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent * Camera;

	APlayerController *PlayerControllerRef;
	bool bIsPlayerAlive = true;

	void Rotate();
	void CalculateRotation(float Value);

	void Traslate();
	void CalculateTraslation(float Value);

	FVector resultTraslation;
	FQuat resultRotation;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "MovementsAjust", meta = (AllowPrivateAccess = "true"))
	float TraslationSpeed = 100.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "MovementsAjust", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 100.0f;

public:
	AAPawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

	UHealthComponent* GetHealthComponent() {return HealthComponent;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
