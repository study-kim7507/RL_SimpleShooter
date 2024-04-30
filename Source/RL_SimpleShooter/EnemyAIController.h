	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 2000.f;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* EnemyAIBehavior;
};
