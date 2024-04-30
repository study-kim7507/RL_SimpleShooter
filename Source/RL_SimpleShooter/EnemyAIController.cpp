// Fill out your copyright notice in the Description page of Project Settings.

// TODO: 현재는 플레이어 컨트롤러가 Posses한 폰을 포커싱(이동)하도록 구현이 되었지만,
	// 추후 학습에서는, 플레이어 컨트롤러가 Posses한 폰이 아닌 상대 폰을 포커싱하도록 구현을 변경 필요.
	// 학습 이후, 플레이어가 직접 게임을 플레이 할 때에도 학습 과정과 동일하게 동작하도록 분기를 나누어 관리할 필요가 있음.

#include "EnemyAIController.h"
#include "ShooterCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();	

	if (EnemyAIBehavior != nullptr)
	{ 
		RunBehaviorTree(EnemyAIBehavior);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}