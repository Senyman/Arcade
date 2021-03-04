
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"			// это для box, должно быть раньше, чем playerpawngenerated.h
#include "Camera/CameraComponent.h"				//это нужно для camera component
#include "Arcade/Components/ShootComponent.h"						// для стрельбы
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class ARCADE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);     
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);   // их заменить. fingerindex это количество пальцев, которое было присоединено 
	// функция срабатывает при нажатии ЛКМ


	virtual void PossessedBy(AController* NewController) override; // что б не делать каст в event tick
	APlayerController* PlayerController;

	FVector2D MoveLimit;	//Ограничение движения в заданных областях

	int NumberOfMaterial;
	
private:
	FVector2D TouchLocation;	// Объявляем эти две переменные, что б узнать положение точки, когда тыкнем на экран
	bool Touching;
	UMaterialInterface* PawnMaterial;	// Объявляю материал корабля, что бы изменить его, когда меня ранят на мигающий 


public:	
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths") // Ф-ю можно перезаписать в BP
	bool CanBeDamaged();				// Может ли по персонажу пройти урон ( не может, если есть щит, то не будет)
	bool CanBeDamaged_Implementation();	// Ф-я, которая будет определять логику с c++

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")	// Делаем BlueprintNativeEvent, что бы в BP можно было повесить какие либо эфекты
	void ExplodePawn();										// Взорвать корабль, когда его жизни = 0
	void ExplodePawn_Implementation();						// Implementation - реализация

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")
	void RecoverPawn();		// Восстановить корабль после воскрешения
	void RecoverPawn_Implementation();
	
	// void ResiveAnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor * DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")		// Макрос
	UBoxComponent* PawnCollision;											// объявили квадратную коллизию кораблю

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;											// ссылка на компонент типа staticmeshcomponent, которая называется pawnmesh

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")		// камера
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")		// объявили шут компонент, добавили его как компонент
	UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")			
	float TouchMoveSensivity;	

	UPROPERTY(BlueprintAssignable, Category = "Healths")
	FPawnDamagedEvent PawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healths")		// Материал корабля будет устанавливаться в редакторе
		UMaterialInterface* RecoverMaterial;									// Будет меняться на этот при взрыве корабля

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* DestroyParticle;

};


