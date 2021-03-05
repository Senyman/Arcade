#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)		// ��� �� ����� ������ � BP ������������
class ARCADE_API ABonus : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABonus();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonuses")
		class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual")
		UParticleSystem* CollectParticle;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent)		// ��� �� ����� ���� ������������ � BP
	void BonusCollected();
	virtual void BonusCollected_Implementation();
	virtual void Tick(float DeltaTime) override;
};
