#include "BonusSlowDownTime3.h"
#include "Engine/World.h"			
#include "TimerManager.h"	


ABonusSlowDownTime3::ABonusSlowDownTime3()
	:
	SlowDownTime(2)

{

}

void ABonusSlowDownTime3::BonusCollected_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 0.5);
	if (CollectParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
	FVector BonusLocation = GetActorLocation();
	FVector NewBonusLocation = BonusLocation + (2000.f);
	SetActorLocation(NewBonusLocation);
	GetWorld()->GetTimerManager().SetTimer(SlowDownTimer, this, &ABonusSlowDownTime3::EndSlowDownTime, SlowDownTime, false);
	UE_LOG(LogTemp, Warning, TEXT("1FunctionWork"));

	
}

void ABonusSlowDownTime3::EndSlowDownTime()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1);
	UE_LOG(LogTemp, Warning, TEXT("2FunctionWork"));
	
}
