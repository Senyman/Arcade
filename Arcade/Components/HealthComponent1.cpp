#include "HealthComponent1.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent1::UHealthComponent1():
	Health(100) {}

void UHealthComponent1::BeginPlay() // Called when the game starts
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent1::OnOwnerDamaged);  // ������������� � ����������
}

void UHealthComponent1::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator1, AActor* DamageCauser)
{
	ChangeHealth(-Damage);  // ����� �������� �����
}

void UHealthComponent1::ChangeHealth(float Value)
{
	Health += Value;
	if (Health <= 0.f)    // ���� ������ ������ 0
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent1::OnOwnerDamaged);
		OnHealthEnded.Broadcast(); // � ������ ����������� ��������� ( ��� ����...)
	}
}

float UHealthComponent1::GetHealth()
{
	return Health;
}

