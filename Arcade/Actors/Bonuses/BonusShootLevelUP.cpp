#include "Arcade/Actors/Bonuses/BonusShootLevelUP.h"
#include "Kismet/GameplayStatics.h"		// Остюда можно взять ссылку на игровой режим и персонажа
#include "Arcade/ArcadeGameMode.h"

void ABonusShootLevelUP::BonusCollected_Implementation()		// Когда взял Бонус
{
	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // Получает игровой режим правил для игры
	if (!Gamemode) return;

	Gamemode->ChangeShootLevel(true);
	Super::BonusCollected_Implementation(); // Что бы вызвалась родительская логика из Bonus
}