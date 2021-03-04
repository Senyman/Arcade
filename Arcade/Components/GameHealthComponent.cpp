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

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0); // Таким образом я получаю своего персонажа

	// PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UGameHealthComponent::OnPlayerDamaged);
	// Вызываю у  PlayerPawn функцию, AddDynamic - это диспатчер и ему нужно указать к какой ф-ии привязываюсь
	// Когда корабль получает какой либо урон, вызывается  UGameHealthComponent::OnPlayerDamaged
}


//void UGameHealthComponent::OnPlayerDamaged()
//{
//	ChangeHealths(-1);
//}

void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healths += ByValue;
	HealthsChanged.Broadcast(ByValue);		// Диспатчер, срабатывает при изменении жизней
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();			// Когда кончаются жизни, вызываем диспатчер из c++
	}

	UE_LOG(LogTemp, Warning, TEXT("FUCK FUCK FUCK: %i"), Healths);
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}


