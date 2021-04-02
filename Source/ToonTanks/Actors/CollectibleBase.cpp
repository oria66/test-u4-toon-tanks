// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleBase.h"
#include "ToonTanks/Pawns/APawnTank.h"

// Sets default values
ACollectibleBase::ACollectibleBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collectible Mesh"));
}

// Called when the game starts or when spawned
void ACollectibleBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACollectibleBase::Overlap);
}

// Called every frame
void ACollectibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollectibleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACollectibleBase::Overlap(AActor* OverlappedActor, AActor* OtherActor) 
{
	AAPawnTank* Tank = Cast<AAPawnTank>(OtherActor);
	
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped!!!!"));
		Destroy();
	}
}

