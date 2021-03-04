#include "BonusPoints3.h"
#include "Kismet/GameplayStatics.h"		// Остюда можно взять ссылку на игровой режим и персонажа
#include "Arcade/ArcadeGameMode.h"

void ABonusPoints3::BonusCollected_Implementation()		// Когда взял Бонус
{

	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // Получает игровой режим правил для игры
	if (Gamemode) Gamemode->AddPoints(Points);	// Если есть правила, то добавить очки
	Destroy();

	Super::BonusCollected_Implementation(); // Что бы вызвалась родительская логика из Bonus
	
}