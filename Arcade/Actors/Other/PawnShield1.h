#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "PawnShield1.generated.h"



UCLASS()
class ARCADE_API APawnShield1 : public AActor
{
	GENERATED_BODY()

protected:
	FTimerHandle ShieldTimer;

	class APlayerPawn* ShieldForPawn;
	
public:	
	APawnShield1();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void ActivateShield(APlayerPawn* PlayerPawn);		// ��� ����� �������� ������ ��� Pawn�

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield")		// ����� ���� ������ ����� ������������ ��������
		float ShieldTime;
};
