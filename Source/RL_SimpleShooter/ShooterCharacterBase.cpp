// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacterBase.h"
#include "Weapon.h"
#include "Armor.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterCharacterBase::AShooterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AShooterCharacterBase::HandleDestruction()
{
	// SetActorHiddenInGame(true);
	// SetActorTickEnabled(false);

	// 현재는 죽으면 바로 레벨에서 객체를 없앰.
	// TODO : 가능하면, 객체를 없애긴보단 컨트롤러를 분리시키고, 콜리전을 제거하여 시체만 남도록 필요.
	// CurrentWeapon->Destroy();
	// CurrentArmor->Destroy();
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AShooterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShooterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShooterCharacterBase::PullTrigger()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->FireWithProjectile(this);
	}
}
