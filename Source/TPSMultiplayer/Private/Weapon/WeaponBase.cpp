// TPSMultiplayer, Tikhonov Gennadii, All Rights Reserved.


#include "Weapon/WeaponBase.h"

#include "Net/UnrealNetwork.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
	SetRootComponent(WeaponMesh);

	DefaultAmmoAmount = 30;
	AmmoAmount = DefaultAmmoAmount;
	ClipsAmount = 3;

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AWeaponBase::LoadAmmo()
{
	if (HasClips())
	{
		AmmoAmount = DefaultAmmoAmount;
		ClipsAmount--;
		return true;
	}
	return false;
}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeaponBase, AmmoAmount);
	DOREPLIFETIME(AWeaponBase, ClipsAmount);
}

bool AWeaponBase::Reload_Implementation()
{
	return false;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Shoot_Implementation()
{
	AmmoAmount = FMath::Clamp(AmmoAmount-1,0,DefaultAmmoAmount);
}
