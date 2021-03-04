// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)		// Что бы могли бонусы в BP использовать
class ARCADE_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

protected:
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent)		// Что бы можно было перезаписать в BP
	void BonusCollected();
	virtual void BonusCollected_Implementation();

	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonuses")	
		class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* CollectParticle;

};
