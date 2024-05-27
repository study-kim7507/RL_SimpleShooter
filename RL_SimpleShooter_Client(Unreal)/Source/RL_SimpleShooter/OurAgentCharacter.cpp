// Fill out your copyright notice in the Description page of Project Settings.

#include "OurAgentCharacter.h"
#include "Armor.h"
#include "Weapon.h"

AOurAgentCharacter::AOurAgentCharacter()
{

}

void AOurAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponNum = 0;
	ArmorNum = 0;
	ChangeWeapon(WeaponNum);
	ChangeArmor(ArmorNum);
}

void AOurAgentCharacter::ChangeWeapon(int32 _WeaponNum)
{
	AWeapon* PreWeapon = nullptr;
	if (CurrentWeapon != nullptr)
	{
		PreWeapon = CurrentWeapon;
	}

	if (Weapons.Num() != 0)
	{
		WeaponNum = _WeaponNum;
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Weapons[_WeaponNum]);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		CurrentWeapon->SetOwner(this);
		if (PreWeapon != nullptr) PreWeapon->Destroy();
	}
}

void AOurAgentCharacter::ChangeArmor(int32 _ArmorNum)
{
	AArmor* PreArmor = nullptr;
	if (CurrentArmor != nullptr)
	{
		PreArmor = CurrentArmor;
	}

	if (Armors.Num() != 0)
	{
		ArmorNum = _ArmorNum;
		CurrentArmor = GetWorld()->SpawnActor<AArmor>(Armors[_ArmorNum]);
		CurrentArmor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("ArmorSocket"));
		CurrentArmor->SetOwner(this);
		if (PreArmor != nullptr) PreArmor->Destroy();
	}
}