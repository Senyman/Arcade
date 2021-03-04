#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent1.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);
// Создаем диспатчер в хедер файле

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UHealthComponent1 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent1();

protected:
	// Called when the game startsB
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UFUNCTION()
		void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
			AController* Instigator1, AActor* DamageCauser); // damageActor - кому нанесли урон

public:	
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealth(float Value);

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthEndedEvent OnHealthEnded;
};
