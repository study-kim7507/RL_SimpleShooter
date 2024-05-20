// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_OurAgentLocation.generated.h"

/**
 * 
 */
UCLASS()
class RL_SIMPLESHOOTER_API UBTService_OurAgentLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_OurAgentLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	void FindOurAgentCharacter();
	class AOurAgentCharacter* OurAgentCharacter;
};

