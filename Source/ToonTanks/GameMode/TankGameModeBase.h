// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class AAPawnTank;
class AAPawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	private:
		AAPawnTank *PlayerTank;
		int32 TargetTurrets = 0;
		APlayerControllerBase *PlayerControllerRef;
	
		int32 GetTargetTurrentCount();
		
		void HandleGameStart();
		void HandleGameOver(bool PlayerWon);

	public:
		ATankGameModeBase();

		void ActorDied(AActor *DeadActor);

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Loop")
		int32 StartDelay = 0;

		virtual void BeginPlay() override;

		UFUNCTION(BlueprintImplementableEvent)
		void GameStart();
		
		UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool PlayerWon);
};
