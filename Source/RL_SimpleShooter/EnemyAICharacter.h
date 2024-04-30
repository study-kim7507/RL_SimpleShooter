// Fill out your copyright notice in the Description page of Project Settings.
// 학습 대상(에이전트)의 상대 캐릭터 언리얼엔진의 비헤이비어 트리를 이용하여 구현

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterBase.h"
#include "EnemyAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API AEnemyAICharacter : public AShooterCharacterBase
{
	GENERATED_BODY()

public:
	AEnemyAICharacter();

protected:
	virtual void BeginPlay() override;

private:
	// 랜덤한 무기, 방어구로 변경하기 위한 함수.
	UFUNCTION(BlueprintCallable)
	void ChangeWeapon();

	UFUNCTION(BlueprintCallable)
	void ChangeArmor();
};	
