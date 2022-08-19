// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MHealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMHealthComponent::UMHealthComponent()
{
	DefaultHealth = 100;

	SetIsReplicated(true);
}


// Called when the game starts
void UMHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &UMHealthComponent::HandleTakeDamage);
		}
	}
	Health = DefaultHealth;
}

void UMHealthComponent::HandleTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"),*FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UMHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMHealthComponent, Health);
}
