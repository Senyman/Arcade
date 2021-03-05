#pragma once
#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "Kismet/GameplayStatics.h"	
#include "BonusSlowDownTime3.generated.h"

UCLASS()
class ARCADE_API ABonusSlowDownTime3 : public ABonus
{
	GENERATED_BODY()

public:
	ABonusSlowDownTime3();		// Конструктор
	FTimerHandle SlowDownTimer;	// Таймер
	float SlowDownTime;

protected:
		virtual void BonusCollected_Implementation() override;
		void EndSlowDownTime();
};
