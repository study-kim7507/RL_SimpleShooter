// Fill out your copyright notice in the Description page of Project Settings.
// 캐릭터의 베이스
// ShooterCharacterBase
	// PlayerCharacter
	// EnemyAICharacter
	// OurAgentCharacter
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacterBase.generated.h"

UCLASS()
class RL_SIMPLESHOOTER_API AShooterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PullTrigger();
	void HandleDestruction();

	class AWeapon* GetCurrentWeapon() { return CurrentWeapon; }
	class AArmor* GetCurrentArmor() { return CurrentArmor; }
	int32 GetCurrentWeaponNum() { return WeaponNum; }
	int32 GetCurrentArmorNum() { return ArmorNum; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<TSubclassOf<class AWeapon>> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<TSubclassOf<class AArmor>> Armors;

	class AWeapon* CurrentWeapon;
	class AArmor* CurrentArmor;

	int32 WeaponNum = 0;
	int32 ArmorNum = 0;

private:
	UPROPERTY(EditDefaultsOnly)
	class UHealthComponent* HealthComponent;
};
