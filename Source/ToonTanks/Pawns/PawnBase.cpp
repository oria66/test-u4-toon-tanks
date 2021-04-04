// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	FVector LookAtObjetive = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtObjetive - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);	
}

void APawnBase::Fire() 
{
	if(ProjectileClass)
	{
		// Si la cantidad de proyectiles es mayor que cero o tiene proyectiles infinitos

		if(Ammo > 0 || Ammo == -1)
		{
			FVector Locator = ProjectileSpawnPoint->GetComponentLocation();
			FRotator Rotator = ProjectileSpawnPoint->GetComponentRotation();

			AProjectileBase *CurrentProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Locator, Rotator);
		
			CurrentProjectile->SetOwner(this);

			if(Ammo > 0)
				Ammo--;
		}
	}
}

void APawnBase::HandleDestruction() 
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

void APawnBase::AddAmmo(const int NewAmmoCount) 
{
	Ammo += NewAmmoCount;
}

int APawnBase::GetAmmo() const
{
	return Ammo;
}