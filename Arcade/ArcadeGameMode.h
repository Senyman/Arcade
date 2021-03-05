#pragma once
#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Arcade/Components/EnemySpawnController.h"
#include "Arcade/Components/GameHealthComponent.h"
#include "Engine/World.h"								// Для таймера
#include "TimerManager.h"								// Тоже для таймера
#include "Arcade/Components/ShootComponent.h"
#include "ArcadeGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);		// Диспатчер при окончании игры

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

	FTimerHandle RecoverTimer;	// Таймер, который будет вызываться на RecoverTimer
	FTimerHandle IncreaceDifficultyTimer;

	bool IsGameOver;			// Конец игры да или нет

public:
	AArcadeGameMode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UEnemySpawnController* EnemySpawnController1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")		
	UGameHealthComponent* HealthsComponent1;		// Добавил HealthsComponent сюда, что б взаимодействовать с игрой, когда персонаж умирает	

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")		// BlueprintCallable позволяет вызвать ф-ю из BP
		void AddPoints(int Points);

	UFUNCTION(BlueprintCallable, Category = "Shooting")		// BlueprintCallable позволяет вызвать ф-ю из BP
		bool ChangeShootLevel(bool Up);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;			// Время за которое восстанавливается игрок

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float IncreaseDifficultyPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")		// Очки за убийство врага или еще за что-то
		int  GamePoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting")		// Очки за убийство врага или еще за что-то
		TArray<FShootInfoLevel> ShootInfoLevels;		// Это паттерн (шаблон), которым мы стреляем, массив с типом стрельюы

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")		// Очки за убийство врага или еще за что-то
		int CurrentShootLevel;
};


 
