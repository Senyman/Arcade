
#include "HealthComponent.h"

// Sets default values
AHealthComponent::AHealthComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthComponent::ChangeHealth(float Value)
{

	Health -= Value;
	if (Health <= 0.f)
	{

	}

}

float AHealthComponent::GetHealth()
{
	return Health;
}



