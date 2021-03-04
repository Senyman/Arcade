// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Pawns/EnemyPawn.h"
#include "EnemySpawnController.generated.h"


// Структура, по которой будут спавнится враги
USTRUCT(BlueprintType) // Что б структура была видна в BP (структура снаряда)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") // Объявляю массив со спавнищиемися противниками, тут находится информация о врагах
	TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// Место спавна
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// Количество врагов, которое спавнится за раз
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// С какой периодичностью спавнится каждый отдельный враг
	float SpawnDelay;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Deactivate() override;		// Встроенная ф-я, поможет остановить спавн врагов
	// Функция, которая спавнит врагов
	void StartSpawnStage();			// Запускает стадию, по которой спавнятся враги
	void SpawnEnemy();				// Будет спавнить конкретно противников
	FEnemySpawnInfo SpawnStage;		// Переменная класса EnemySpawnInfo
	int EnemiesSpawned;				// Для остановки таймера, после того, как все мобы заспавнятся
	FTimerHandle ChangeStageTimer;	// Таймер, таймер который меняет стадии спавна массива врагов
	FTimerHandle EnemySpawnTimer;	// Таймер спавна врагов 
	FRandomStream Random;			// Объявляем рандомное число

public:	

	
	// Игра должна случайным образом выбирать спавн из чегото, поэтому будет массив с массивами набора спавна врагов

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// Массив с волной врагов
	TArray <FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMinDelay;												 // Задержка, с которой спавнятся группы противников

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		float ChangeStageTimeMultiplier;
};
