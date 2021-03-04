// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.generated.h"

UCLASS()
class ARCADE_API AHealthComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealth(float Value);


	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();
	
};
