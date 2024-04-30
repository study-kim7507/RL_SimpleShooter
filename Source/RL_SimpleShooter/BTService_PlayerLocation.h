// Fill out your copyright notice in the Description page of Project Settings.
// 현재 구현은 플레이어폰을 기준으로 구현되어있음.
// 추후 학습 에이전트, 플레이어폰 모두 처리할 수 있도록 구현을 변경해야함.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
