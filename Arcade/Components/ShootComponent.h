#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)	// Макрос, дает доступность структуры снаряда в BP 
struct FShootInfo		// Определяем структуру
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")	// Сдвиг спавна снаряда вправо или влево
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Angle;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle ShootingTimer;		// Это переменная таймера
	void Shoot();					// Функция стрельбы

public:
	UFUNCTION(BlueprintCallable, Category = "Shooting")						// Макрос для создания функций, который может быть в BP's, Callable для того, что б ф-я была не Pure
		void StartShooting();												// Метод для начала стрельбы, ниже для конца

	UFUNCTION(BlueprintCallable, Category = "Shooting")						// Макрос для создания функций, который может быть в BP's, Callable для того, что б ф-я была не Pure
		void StopShooting();

	float ShootPeriod;
	TArray<FShootInfo> ShootInfos;										//	Объект типа массив структуры ShootInfo с различными параметрами
};