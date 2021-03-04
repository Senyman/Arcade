#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UGameHealthComponent::UGameHealthComponent():
	Healths(3)
{
}


void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0); // ����� ������� � ������� ������ ���������

	// PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UGameHealthComponent::OnPlayerDamaged);
	// ������� �  PlayerPawn �������, AddDynamic - ��� ��������� � ��� ����� ������� � ����� �-�� ������������
	// ����� ������� �������� ����� ���� ����, ����������  UGameHealthComponent::OnPlayerDamaged
}


//void UGameHealthComponent::OnPlayerDamaged()
//{
//	ChangeHealths(-1);
//}

void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healths += ByValue;
	HealthsChanged.Broadcast(ByValue);		// ���������, ����������� ��� ��������� ������
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();			// ����� ��������� �����, �������� ��������� �� c++
	}

	UE_LOG(LogTemp, Warning, TEXT("FUCK FUCK FUCK: %i"), Healths);
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}


