#pragma once
#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Arcade/Components/EnemySpawnController.h"
#include "Arcade/Components/GameHealthComponent.h"
#include "Engine/World.h"								// ��� �������
#include "TimerManager.h"								// ���� ��� �������
#include "Arcade/Components/ShootComponent.h"
#include "ArcadeGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);		// ��������� ��� ��������� ����

USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};

UCLASS(minimalapi)
class AArcadeGameMode : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	FTimerHandle RecoverTimer;	// ������, ������� ����� ���������� �� RecoverTimer
	FTimerHandle IncreaceDifficultyTimer;

	bool IsGameOver;			// ����� ���� �� ��� ���

public:
	AArcadeGameMode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UEnemySpawnController* EnemySpawnController1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")		
	UGameHealthComponent* HealthsComponent1;		// ������� HealthsComponent ����, ��� � ����������������� � �����, ����� �������� �������	

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")		// BlueprintCallable ��������� ������� �-� �� BP
		void AddPoints(int Points);

	UFUNCTION(BlueprintCallable, Category = "Shooting")		// BlueprintCallable ��������� ������� �-� �� BP
		bool ChangeShootLevel(bool Up);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;			// ����� �� ������� ����������������� �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float IncreaseDifficultyPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")		// ���� �� �������� ����� ��� ��� �� ���-��
		int  GamePoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting")		// ���� �� �������� ����� ��� ��� �� ���-��
		TArray<FShootInfoLevel> ShootInfoLevels;		// ��� ������� (������), ������� �� ��������, ������ � ����� ��������

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")		// ���� �� �������� ����� ��� ��� �� ���-��
		int CurrentShootLevel;
};


 
