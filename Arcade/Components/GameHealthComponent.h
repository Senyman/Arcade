// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"

			
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthsEndedEvent); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthsChangedEvent, int, ChangeValue); // Диспатчер, вызывается при изменении жизней, тут параметр
// Для поддержки параметров в макрос нужно добавить строчку oneparam

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game Health")
	int Healths;

	
public:

	UFUNCTION(BlueprintCallable, Category = "Game Health")
		void ChangeHealths(int ByValue);						// Функция для изменения жизней

	UFUNCTION(BlueprintPure, Category = "Game Health")
		int GetHealths();

	UPROPERTY(BlueprintAssignable, Category = "Game Health")	// Тут мы делаем сам диспатчер, доступный в BP
	FHealthsEndedEvent HealthsEnded;							// и называем его HealthEnded

	UPROPERTY(BlueprintAssignable, Category = "Game Health")	// Определяю диспатчер для изменения жизней у игрока
		FHealthsChangedEvent HealthsChanged;
};

