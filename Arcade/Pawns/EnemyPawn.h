// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"			// это для box, должно быть раньше, чем playerpawngenerated.h
#include "Arcade/Components/ShootComponent.h"						// для стрельбы
#include "Arcade/Components/HealthComponent1.h"			// Для здоровья врага
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "EnemyPawn.generated.h"


// Структура, в которой будет шанс выпода, описан тип бонуса и др. при смерти врага
USTRUCT(BlueprintType)
struct FBonusChance			// В плюсах всегда структуры идут с приставкой F
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		TSubclassOf<class ABonus> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		float Chance;
};


UCLASS()
class ARCADE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnBonuses();

	UFUNCTION()
		void KillPawn();
	
	UFUNCTION()
		void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
		void DestroyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")			// коллизия корабля видна везде, доступна для чтения в bp
		UBoxComponent* PawnCollision;											// объявили квадратную коллизию кораблю

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")			// объявили шут компонент, добавили его как компонент
		UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")			// объявили шут компонент, добавили его как компонент
		UHealthComponent1* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
		int DestroyPoints;														// Очки, которые будут добавляться при смерти врага

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus")			// Массив бонусов, которые могут заспавниться
		TArray<FBonusChance> PossibleBonuses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* DestroyParticle;

};
