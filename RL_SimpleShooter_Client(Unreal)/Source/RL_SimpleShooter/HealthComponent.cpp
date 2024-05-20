// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ShooterCharacterBase.h"
#include "Weapon.h"
#include "Armor.h"
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

bool UHealthComponent::IsDead() const 
{
	return CurrentHealth <= 0.f;
}

float UHealthComponent::GetCurrentHealthPercentage() const
{
	return CurrentHealth / MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	// DamageCauser(Projectile)의 Owner인 Weapon을 소유한 Character -> Attacker
	AShooterCharacterBase* Attacker = Cast<AShooterCharacterBase>(Instigator->GetPawn());
	if (Attacker == nullptr) return;

	// Attacker의 현재 무기 번호
	int32 AttackerCurrentWeaponNum = Attacker->GetCurrentWeaponNum();

	// Attacker의 공격을 맞은(방어)한 사람(Character)
	AShooterCharacterBase* Defensor = Cast<AShooterCharacterBase>(DamagedActor);
	if (Defensor == nullptr) return;

	// Defensor의 현재 방어구 번호
	int32 DefensorCurrentArmorNum = Defensor->GetCurrentArmorNum();

	// 공격자의 무기 번호와 방어자의 방어구 번호가 같음
	// 같은 경우, 절반의 피해만
	if (AttackerCurrentWeaponNum == DefensorCurrentArmorNum)
	{
		RecvDamage = Damage * 0.5;
		CurrentHealth -= RecvDamage;
	}

	// 다른 경우, 모든 피해
	else
	{
		RecvDamage = Damage;
		CurrentHealth -= RecvDamage;
	}

	if (GameMode == nullptr) return;
	if (CurrentHealth <= 0.f)
		GameMode->ActorDied(Defensor);

	UE_LOG(LogTemp, Warning, TEXT("Current Health : %f, %f"), CurrentHealth, RecvDamage);
}
