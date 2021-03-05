//#include "BonusSlowDownTime.h"
//#include "Arcade/ArcadeGameMode.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"			// Для таймера
//#include "TimerManager.h"			// Тоже для таймера
//
//
//ABonusSlowDownTime::ABonusSlowDownTime()
//	:
//	SlowDownTime(2)
//{
//}
//
//void ABonusSlowDownTime::DeactivateSlowDownTime1()
//{
//	UGameplayStatics::SetGlobalTimeDilation(this, 1);
//}
//
//void ABonusSlowDownTime::BonusCollected_Implementation()		// Когда взял Бонус
//{
//	UGameplayStatics::SetGlobalTimeDilation(this, 2);
//	UE_LOG(LogTemp, Log, TEXT("EndFunction"));
//}
//
//
