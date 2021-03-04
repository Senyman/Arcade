// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"			// ��� ��� box, ������ ���� ������, ��� playerpawngenerated.h
#include "Arcade/Components/ShootComponent.h"						// ��� ��������
#include "Arcade/Components/HealthComponent1.h"			// ��� �������� �����
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "EnemyPawn.generated.h"


// ���������, � ������� ����� ���� ������, ������ ��� ������ � ��. ��� ������ �����
USTRUCT(BlueprintType)
struct FBonusChance			// � ������ ������ ��������� ���� � ���������� F
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")			// �������� ������� ����� �����, �������� ��� ������ � bp
		UBoxComponent* PawnCollision;											// �������� ���������� �������� �������

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")			// �������� ��� ���������, �������� ��� ��� ���������
		UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")			// �������� ��� ���������, �������� ��� ��� ���������
		UHealthComponent1* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
		int DestroyPoints;														// ����, ������� ����� ����������� ��� ������ �����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus")			// ������ �������, ������� ����� ������������
		TArray<FBonusChance> PossibleBonuses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* DestroyParticle;

};
