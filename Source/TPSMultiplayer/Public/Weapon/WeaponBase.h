// TPSMultiplayer, Tikhonov Gennadii, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;

UCLASS(Abstract)
class TPSMULTIPLAYER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Shoot")
	void Shoot();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Shoot")
	bool Reload();

	UFUNCTION(BlueprintCallable, Category="Ammo")
	bool LoadAmmo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ammo")
	bool HasAmmo(){return AmmoAmount > 0;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ammo")
	bool HasClips(){return ClipsAmount > 0;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ammo")
	int GetAmmo(){return AmmoAmount;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ammo")
	int GetDefaultAmmo(){return DefaultAmmoAmount;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ammo")
	int GetClips(){return ClipsAmount;}
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon", meta=(AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category="Ammo", meta=(AllowPrivateAccess, ClampMin = "0"))
	int DefaultAmmoAmount;

	UPROPERTY(Replicated, EditDefaultsOnly, Category="Ammo", meta=(AllowPrivateAccess, ClampMin = "0"))
	int AmmoAmount;

	UPROPERTY(Replicated, EditDefaultsOnly, Category="Ammo", meta=(AllowPrivateAccess, ClampMin = "0"))
	int ClipsAmount;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
