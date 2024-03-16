// TPSMultiplayer, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HealthComponent, Display, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Health);

UCLASS( ClassGroup=(HealthComponent), meta=(BlueprintSpawnableComponent) )
class TPSMULTIPLAYER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UHealthComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	float GetHealth(){return Health;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	float GetDefaultHealth(){return DefaultHealth;}

	UPROPERTY(BlueprintAssignable, Category = "Death")
	FOnDeathSignature OnDeath;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedSignature OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(NetMulticast, Reliable)
	void DoDeath();
	
	UPROPERTY(EditDefaultsOnly, Category="Health", meta=(ClampMin = "0"))
	float DefaultHealth = 100.f;

	UPROPERTY(Replicated)
	float Health;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;
		
};
