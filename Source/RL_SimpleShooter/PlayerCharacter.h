// Fill out your copyright notice in the Description page of Project Settings.
// 학습이 완료된 이후, 플레이어 컨트롤러가 Posses하여 조종하게 될 캐릭터
#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API APlayerCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	// 액션 매핑을 위함. 움직임
	void MoveForward(float Value);
	void MoveRight(float Value);

	// 사용자의 입력에 따라 순차적으로 무기와 방어구를 바꾸기 위함.
	UFUNCTION()
	void ChangeWeapon();
	UFUNCTION()
	void ChangeArmor();
};
