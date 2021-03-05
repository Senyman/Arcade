#pragma once
#include "CoreMinimal.h"
#include "Bonus.h"
#include "BonusShootLevelUP.generated.h"

UCLASS()
class ARCADE_API ABonusShootLevelUP : public ABonus
{
	GENERATED_BODY()
protected:
	virtual void BonusCollected_Implementation() override;
};