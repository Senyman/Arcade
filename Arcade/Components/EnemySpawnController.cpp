#include "EnemySpawnController.h"
#include "Engine/World.h"			// ��� �������
#include "TimerManager.h"			// ���� ��� �������


void UEnemySpawnController::BeginPlay()
	
{
	Super::BeginPlay();
	Random.GenerateNewSeed();		// ��� �� �� ���� ����������
	StartSpawnStage();
}


void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();		
	// ��� ������� �������, ��� �-� Deactivate is basic = BaseClass::Foo()  disappears - ��������
	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UEnemySpawnController::StartSpawnStage()
{
	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];   // �������� ��������� �����, ������� ����� �������� ������ ������ ������
	EnemiesSpawned = 0;
	SpawnEnemy();
	
	// ���� ��������� ������, ������� ����� �������� ������

	float ChangeStadeTime = Random.RandRange(StageMinDelay, StageMaxDelay)* ChangeStageTimeMultiplier;
	GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnController::StartSpawnStage, ChangeStadeTime, false);		
	// ������ ������ �� �������, SetTimer - �-�, ������� �� ��������� �������� ������ �-�
}

void UEnemySpawnController::SpawnEnemy()
{
	// UE_LOG(LogTemp, Log, TEXT("SpawnEnemy"));

	FActorSpawnParameters SpawnParametrs;
	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParametrs); 
	// ������ ���, ����� ���������� spawnenemy, ��������� ����, � ������� ���� ��������� ���������
	
	EnemiesSpawned++;								// � ������ ������� ����� ����� ����������� ���� �������
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);		
		// spawnenemy ��� �-�, ������� ����� ���������� �� �������
		// GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer); //	���������� ������ ��� ���������� ������������ �������
	}
}



