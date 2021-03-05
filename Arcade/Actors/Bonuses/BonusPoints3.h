#pragma once
#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "BonusPoints3.generated.h"

UCLASS()
class ARCADE_API ABonusPoints3 : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusCollected_Implementation() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonuses")
		int Points;		// Количество добавляемых поинтов
};
