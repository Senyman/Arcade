// Fill out your copyright notice in the Description page of Project Settings.
// Этот файл отвечает за триггер, при выходе из которогго уничтожается любой объект
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaygroundBorder.generated.h"

UCLASS()
class ARCADE_API APlaygroundBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaygroundBorder();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
