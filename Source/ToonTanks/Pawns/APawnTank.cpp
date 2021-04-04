// Fill out your copyright notice in the Description page of Project Settings.


#include "APawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AAPawnTank::AAPawnTank()
{
    SpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AAPawnTank::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerRef = Cast<APlayerController>(GetController());
    
	Ammo = 10;
}

// Called every frame
void AAPawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Traslate();

    if(PlayerControllerRef)
    {
        FHitResult Result;

        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, Result);
        FVector ImpactVector = Result.ImpactPoint;

        RotateTurret(ImpactVector);
    }
}

// Called to bind functionality to input
void AAPawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AAPawnTank::CalculateTraslation);
    PlayerInputComponent->BindAxis("Turn", this, &AAPawnTank::CalculateRotation);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAPawnTank::Fire);
}

void AAPawnTank::HandleDestruction() 
{
    Super::HandleDestruction();

    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool AAPawnTank::GetIsPlayerAlive() 
{
    return bIsPlayerAlive;
}

void AAPawnTank::Rotate() 
{
    AddActorLocalRotation(resultRotation, true);
}

void AAPawnTank::CalculateRotation(float Value) 
{
    float result = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator rot = FRotator(0, result, 0);
    resultRotation = FQuat(rot);
}

void AAPawnTank::Traslate() 
{
    AddActorLocalOffset(resultTraslation, true);
}

void AAPawnTank::CalculateTraslation(float Value) 
{
    resultTraslation = FVector(Value * TraslationSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}
