// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_OurAgentLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacterBase.h"
#include "OurAgentCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTService_OurAgentLocation::UBTService_OurAgentLocation()
{
	NodeName = TEXT("Update OurAgent Location");
	FindOurAgentCharacter();
}

void UBTService_OurAgentLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OurAgentCharacter == nullptr)
		return;
	
	FVector OurAgentCharacterLocation = OurAgentCharacter->GetActorLocation();
	OurAgentCharacterLocation.Z = 0.f;
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), OurAgentCharacterLocation);
}

// 레벨에 배치된 액터들 중 OurAgentCharacter를 찾는 함수.
void UBTService_OurAgentLocation::FindOurAgentCharacter()
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
