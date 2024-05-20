// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_OurAgentLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacterBase.h"
#include "EnemyAIController.h"
#include "OurAgentCharacter.h"

UBTService_OurAgentLocationIfSeen::UBTService_OurAgentLocationIfSeen()
{
	NodeName = TEXT("Update OurAgent Location If Seen");
	FindOurAgentCharacter();
}

void UBTService_OurAgentLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OurAgentCharacter == nullptr)
		return;

	if (OwnerComp.GetAIOwner() == nullptr)
		return;
	
	if (OwnerComp.GetAIOwner()->LineOfSightTo(OurAgentCharacter))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), OurAgentCharacter);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}



// 레벨에 배치된 액터들 중 OurAgentCharacter를 찾는 함수.
void UBTService_OurAgentLocationIfSeen::FindOurAgentCharacter()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOurAgentCharacter::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		OurAgentCharacter = Cast<AOurAgentCharacter>(Actor);
		if (OurAgentCharacter != nullptr)
		{
			return;
		}
	}

	return;
}
