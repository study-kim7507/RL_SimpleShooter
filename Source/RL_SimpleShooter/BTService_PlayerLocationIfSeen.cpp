// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacterBase.h"
#include "EnemyAIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterCharacterBase* PlayerCharacter = Cast<AShooterCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter == nullptr) 
		return;

	if (OwnerComp.GetAIOwner() == nullptr) 
		return;

	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerCharacter))
	{
		/*
		// 캐릭터의 키가 큰 경우, 길찾기를 실패하는 문제로 인해 Z축 값을 0으로 세팅.
		FVector PlayerCharacterLocation = PlayerCharacter->GetActorLocation();
		PlayerCharacterLocation.Z = 0.f;
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerCharacterLocation);
		*/

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerCharacter);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}