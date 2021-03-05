#include "BonusPoints3.h"
#include "Kismet/GameplayStatics.h"		// Для ссылки на игровой режим и персонажа
#include "Arcade/ArcadeGameMode.h"

void ABonusPoints3::BonusCollected_Implementation()		// Подобрал бонус
{
	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // Получает игровой режим правил для игры
	if (Gamemode) Gamemode->AddPoints(Points);
	Destroy();

	Super::BonusCollected_Implementation(); // Что бы вызвалась родительская логика из Bonus
}