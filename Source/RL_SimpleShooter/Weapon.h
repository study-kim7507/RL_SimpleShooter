// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class RL_SIMPLESHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION()
	void FireWithProjectile(const class AShooterCharacterBase* _Owner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY()
	class AProjectile* Projectile;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* FireParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ChangeWeaponSound;

};
