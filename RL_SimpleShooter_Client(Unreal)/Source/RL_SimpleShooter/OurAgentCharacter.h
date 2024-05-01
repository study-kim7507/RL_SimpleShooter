// Fill out your copyright notice in the Description page of Project Settings.
// 학습 대상이 될 캐릭터
#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterBase.h"
#include "OurAgentCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API AOurAgentCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()

public:
	AOurAgentCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 현재는 서버와의 통신을 확인하기 위해
	// 서버에서 생성된 난수를 클라이언트(언리얼)로 받아와 우리의 에이전트가 무기, 방어구를 바꾸도록
	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(int32 WeaponNum);

	UFUNCTION(BlueprintCallable)
	void ChangeArmor(int32 ArmorNum);

};
