// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "Armor.h"
#include "Weapon.h"

AEnemyAICharacter::AEnemyAICharacter()
{

}

void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponNum = -1;
	ArmorNum = -1;
	ChangeWeapon();
	ChangeArmor();
}

void AEnemyAICharacter::ChangeWeapon()
{
	// WeaponNum = FMath::RandRange(0, Weapons.Num()-1);
	AWeapon* PreWeapon = nullptr;
	if (CurrentWeapon != nullptr)
	{
		PreWeapon = CurrentWeapon;
	}

	if (Weapons.Num() != 0)
	{
		WeaponNum++;
		if (WeaponNum >= Weapons.Num()) WeaponNum = 0;
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Weapons[WeaponNum]);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		CurrentWeapon->SetOwner(this);
		if (PreWeapon != nullptr) PreWeapon->Destroy();
	}
}

void AEnemyAICharacter::ChangeArmor()
{
	// ArmorNum = FMath::RandRange(0, Armors.Num() - 1);
	AArmor* PreArmor = nullptr;
	if (CurrentArmor != nullptr)
	{
		PreArmor = CurrentArmor;
	}

	if (Armors.Num() != 0)
	{
		ArmorNum++;
		if (ArmorNum >= Armors.Num()) ArmorNum = 0;
		CurrentArmor = GetWorld()->SpawnActor<AArmor>(Armors[ArmorNum]);
		CurrentArmor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("ArmorSocket"));
		CurrentArmor->SetOwner(this);
		if (PreArmor != nullptr) PreArmor->Destroy();
	}
}