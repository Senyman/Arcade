#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Engine/World.h"			// Для таймера
#include "Arcade/Actors/Other/PawnShield1.h"


void ABonusShield::BonusCollected_Implementation()		// Когда взял Бонус
{

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);	// Ссылка на игрока
	if (!PlayerPawn || !PlayerPawn->bCanBeDamaged) return;
	Super::BonusCollected_Implementation(); // Что бы вызвалась родительская логика из Bonus

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// Это связано с пересечением объекта с чем-то при спавне
	// Объект в любом случае заспавнится

	APawnShield1* Shield = GetWorld()->SpawnActor<APawnShield1>(ShieldClass, SpawnParams);	// Класс, который я буду спавнить
	// SpawnParams отвечает за опции спавна

	if(Shield) Shield->ActivateShield(PlayerPawn);		// Спавним щит для PlayerPawn

	

}