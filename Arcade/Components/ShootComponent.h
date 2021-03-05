#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)	// ������, ���� ����������� ��������� ������� � BP 
struct FShootInfo		// ���������� ���������
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")	// ����� ������ ������� ������ ��� �����
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

	FTimerHandle ShootingTimer;		// ��� ���������� �������
	void Shoot();					// ������� ��������

public:
	UFUNCTION(BlueprintCallable, Category = "Shooting")						// ������ ��� �������� �������, ������� ����� ���� � BP's, Callable ��� ����, ��� � �-� ���� �� Pure
		void StartShooting();												// ����� ��� ������ ��������, ���� ��� �����

	UFUNCTION(BlueprintCallable, Category = "Shooting")						// ������ ��� �������� �������, ������� ����� ���� � BP's, Callable ��� ����, ��� � �-� ���� �� Pure
		void StopShooting();

	float ShootPeriod;
	TArray<FShootInfo> ShootInfos;										//	������ ���� ������ ��������� ShootInfo � ���������� �����������
};