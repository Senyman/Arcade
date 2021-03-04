// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Pawns/EnemyPawn.h"
#include "EnemySpawnController.generated.h"


// ���������, �� ������� ����� ��������� �����
USTRUCT(BlueprintType) // ��� � ��������� ���� ����� � BP (��������� �������)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") // �������� ������ �� ������������� ������������, ��� ��������� ���������� � ������
	TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// ����� ������
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// ���������� ������, ������� ��������� �� ���
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// � ����� �������������� ��������� ������ ��������� ����
	float SpawnDelay;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Deactivate() override;		// ���������� �-�, ������� ���������� ����� ������
	// �������, ������� ������� ������
	void StartSpawnStage();			// ��������� ������, �� ������� ��������� �����
	void SpawnEnemy();				// ����� �������� ��������� �����������
	FEnemySpawnInfo SpawnStage;		// ���������� ������ EnemySpawnInfo
	int EnemiesSpawned;				// ��� ��������� �������, ����� ����, ��� ��� ���� �����������
	FTimerHandle ChangeStageTimer;	// ������, ������ ������� ������ ������ ������ ������� ������
	FTimerHandle EnemySpawnTimer;	// ������ ������ ������ 
	FRandomStream Random;			// ��������� ��������� �����

public:	

	
	// ���� ������ ��������� ������� �������� ����� �� ������, ������� ����� ������ � ��������� ������ ������ ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")	// ������ � ������ ������
	TArray <FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMinDelay;												 // ��������, � ������� ��������� ������ �����������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		float ChangeStageTimeMultiplier;
};
