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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon", meta=(AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	

};
