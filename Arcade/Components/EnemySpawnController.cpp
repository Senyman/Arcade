#include "EnemySpawnController.h"
#include "Engine/World.h"			// Для таймера
#include "TimerManager.h"			// Тоже для таймера


void UEnemySpawnController::BeginPlay()
	
{
	Super::BeginPlay();
	Random.GenerateNewSeed();		// Что бы не было повторений
	StartSpawnStage();
}


void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();		
	// Эта строчка говорит, что ф-я Deactivate is basic = BaseClass::Foo()  disappears - исчезает
	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UEnemySpawnController::StartSpawnStage()
{
	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];   // Выбираем рандомное число, которое будет индексом стадии спавна врагов
	EnemiesSpawned = 0;
	SpawnEnemy();
	
	// Надо запустить таймер, который будет спавнить врагов

	float ChangeStadeTime = Random.RandRange(StageMinDelay, StageMaxDelay)* ChangeStageTimeMultiplier;
	GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnController::StartSpawnStage, ChangeStadeTime, false);		
	// Меняем стадию по таймеру, SetTimer - ф-я, которая по истечению вызывает другую ф-ю
}

void UEnemySpawnController::SpawnEnemy()
{
	// UE_LOG(LogTemp, Log, TEXT("SpawnEnemy"));

	FActorSpawnParameters SpawnParametrs;
	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParametrs); 
	// Каждый раз, когда вызывается spawnenemy, спавнится враг, в котором есть различные параметры
	
	EnemiesSpawned++;								// С каждым спавном врага будет прибавлятся этот счетчик
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);		
		// spawnenemy это ф-я, которая будет вызываться по таймеру
		// GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer); //	Отключение спавна при выполнении необходимого условия
	}
}



