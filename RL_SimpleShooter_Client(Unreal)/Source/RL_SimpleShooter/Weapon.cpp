// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "ShooterCharacterBase.h"
#include "Projectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (ChangeWeaponSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ChangeWeaponSound, GetActorLocation());
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::FireWithProjectile(const AShooterCharacterBase* _Owner)
{
	FVector StartLocation = ProjectileSpawnPoint->GetComponentLocation();
	FVector EndLocation = _Owner->GetController()->GetControlRotation().Vector() + StartLocation;
	FVector Direction = EndLocation - StartLocation;
	Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass);

	if (Projectile != nullptr)
	{
		Projectile->SetOwner(this); 
		Projectile->SetActorLocation(StartLocation);
		Projectile->SetActorRotation(Direction.Rotation());
		Projectile->AddActorLocalRotation(FRotator(-90, 0, 0));

		if (Direction.Normalize())
		{
			if (FireParticle != nullptr && FireSound != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, StartLocation);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, StartLocation);
			}
			Projectile->Fire(Direction);
		}
	}
	
}

