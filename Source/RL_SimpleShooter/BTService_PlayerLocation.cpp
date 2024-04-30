// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacterBase.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterCharacterBase* PlayerCharacter = Cast<AShooterCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter == nullptr)
		return;

	FVector PlayerCharacterLocation = PlayerCharacter->GetActorLocation();
	PlayerCharacterLocation.Z = 0.f;
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerCharacterLocation);
}