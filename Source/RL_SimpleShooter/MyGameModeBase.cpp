// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "EngineUtils.h"
#include "ShooterCharacterBase.h"
#include "PlayerCharacterController.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

void AMyGameModeBase::ActorDied(AActor* DeadActor)
{
	// TODO: 현재는 플레이어 캐릭터가 죽는경우, EnemyAI 캐릭터가 죽는 경우만 구현
	// 학습 대상 (에이전트)가 죽는 경우도 구현필요.
	AShooterCharacterBase* DeadCharacter = Cast<AShooterCharacterBase>(DeadActor);
	if (DeadCharacter == nullptr) return;
	
	// 만약 죽은 캐릭터가 플레이어 캐릭터인 경우 게임 패배
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(DeadCharacter->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// 만약 죽은 캐릭터가 EnemyAI 캐릭터인 경우, EnemyAI 캐릭터를 조종하는 컨트롤러의 수를 파악
	// 현재 죽은 캐릭터의 컨트롤러가 Detach 되었을 경우, 아무런 EnemyAI 컨트롤러가 남지 않는 경우
	// 해당 게임은 플레이어의 승리.
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(DeadCharacter->GetController());
	if (EnemyAIController != nullptr)
	{
		TArray<AActor*> EnemyAIControllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), EnemyAIControllers);
		
		int32 EnemyAICount = EnemyAIControllers.Num();
		EnemyAICount--;
		
		if (EnemyAICount == 0)
		{
			EndGame(true);	
		}
		
	}
	DeadCharacter->HandleDestruction();
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AShooterCharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AMyGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		
	}
}