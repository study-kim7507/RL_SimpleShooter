// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::PullTrigger);
	PlayerInputComponent->BindAction(TEXT("ChangeWeapon"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction(TEXT("ChangeArmor"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeArmor);
}


void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ChangeWeapon();
	ChangeArmor();
}
void APlayerCharacter::ChangeWeapon()
{
	if (WeaponNum >= Weapons.Num()) WeaponNum = 0;
	AWeapon* PreWeapon = nullptr;
	if (CurrentWeapon != nullptr)
	{
		PreWeapon = CurrentWeapon;
	}

	if (Weapons.Num() != 0)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Weapons[WeaponNum]);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		CurrentWeapon->SetOwner(this);
		if (PreWeapon != nullptr) PreWeapon->Destroy();
		WeaponNum++;
	}
}

void APlayerCharacter::ChangeArmor()
{
	if (ArmorNum >= Armors.Num()) ArmorNum = 0;
	AArmor* PreArmor = nullptr;
	if (CurrentArmor != nullptr)
	{
		PreArmor = CurrentArmor;
	}

	if (Armors.Num() != 0)
	{
		CurrentArmor = GetWorld()->SpawnActor<AArmor>(Armors[ArmorNum]);
		CurrentArmor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("ArmorSocket"));
		CurrentArmor->SetOwner(this);
		if (PreArmor != nullptr) PreArmor->Destroy();
		ArmorNum++;
	}
}