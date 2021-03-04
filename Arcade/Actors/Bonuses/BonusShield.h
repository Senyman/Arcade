// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "BonusShield.generated.h"

class APawnShield1;
UCLASS()
class ARCADE_API ABonusShield : public ABonus
{
GENERATED_BODY()

protected:
	
	virtual void BonusCollected_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf  <APawnShield1> ShieldClass;		// ������ �� �����, ������� � ���� ��������

};
