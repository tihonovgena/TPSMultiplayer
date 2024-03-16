// TPSMultiplayer, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponents/HealthComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(HealthComponent)

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Health = DefaultHealth;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ComponentOwner = GetOwner();
	check(ComponentOwner)
	ComponentOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									   AController* InstigatedBy, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.f , DefaultHealth);
	UE_LOG(HealthComponent, Display, TEXT("%s take %f damage"), *ComponentOwner->GetName(), Damage);
	OnHealthChanged.Broadcast(Health);
	UE_LOG(HealthComponent, Display, TEXT("New health: %f"), Health);

	if (Health == 0)
	{
		DoDeath();
	}
}

void UHealthComponent::DoDeath_Implementation()
{
	OnDeath.Broadcast();
	UE_LOG(HealthComponent, Display, TEXT("Character dead"));
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, Health);
}
