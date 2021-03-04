#include "BonusSlowDownTime.h"
#include "Arcade/ArcadeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"			// ��� �������
#include "TimerManager.h"			// ���� ��� �������


ABonusSlowDownTime::ABonusSlowDownTime()
	:
	SlowDownTime(2)
{

}


void ABonusSlowDownTime::DeactivateSlowDownTime1()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1);
	// Destroy();
}



void ABonusSlowDownTime::BonusCollected_Implementation()		// ����� ���� �����
{
	
	UGameplayStatics::SetGlobalTimeDilation(this, 2);
	// BonusLocation = GetActorLocation();
	//FVector NewBonusLocation = BonusLocation + (1000.f);
	//SetActorLocation(NewBonusLocation);
	//GetWorld()->GetTimerManager().SetTimer(SlowDownTimer1, this, &ABonusSlowDownTime::DeactivateSlowDownTime2, SlowDownTime, true);
	//GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer12345, this, &ABonusSlowDownTime::Dea, 3, false);
	
	UE_LOG(LogTemp, Log, TEXT("EndFunction"));
}


