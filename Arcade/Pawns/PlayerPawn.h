
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"			// ��� ��� box, ������ ���� ������, ��� playerpawngenerated.h
#include "Camera/CameraComponent.h"				//��� ����� ��� camera component
#include "Arcade/Components/ShootComponent.h"						// ��� ��������
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
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);   // �� ��������. fingerindex ��� ���������� �������, ������� ���� ������������ 
	// ������� ����������� ��� ������� ���


	virtual void PossessedBy(AController* NewController) override; // ��� � �� ������ ���� � event tick
	APlayerController* PlayerController;

	FVector2D MoveLimit;	//����������� �������� � �������� ��������

	int NumberOfMaterial;
	
private:
	FVector2D TouchLocation;	// ��������� ��� ��� ����������, ��� � ������ ��������� �����, ����� ������ �� �����
	bool Touching;
	UMaterialInterface* PawnMaterial;	// �������� �������� �������, ��� �� �������� ���, ����� ���� ����� �� �������� 


public:	
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths") // �-� ����� ������������ � BP
	bool CanBeDamaged();				// ����� �� �� ��������� ������ ���� ( �� �����, ���� ���� ���, �� �� �����)
	bool CanBeDamaged_Implementation();	// �-�, ������� ����� ���������� ������ � c++

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")	// ������ BlueprintNativeEvent, ��� �� � BP ����� ���� �������� ����� ���� ������
	void ExplodePawn();										// �������� �������, ����� ��� ����� = 0
	void ExplodePawn_Implementation();						// Implementation - ����������

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")
	void RecoverPawn();		// ������������ ������� ����� �����������
	void RecoverPawn_Implementation();
	
	// void ResiveAnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor * DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")		// ������
	UBoxComponent* PawnCollision;											// �������� ���������� �������� �������

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;											// ������ �� ��������� ���� staticmeshcomponent, ������� ���������� pawnmesh

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")		// ������
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")		// �������� ��� ���������, �������� ��� ��� ���������
	UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")			
	float TouchMoveSensivity;	

	UPROPERTY(BlueprintAssignable, Category = "Healths")
	FPawnDamagedEvent PawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healths")		// �������� ������� ����� ��������������� � ���������
		UMaterialInterface* RecoverMaterial;									// ����� �������� �� ���� ��� ������ �������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* DestroyParticle;

};


