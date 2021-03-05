#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"			// Для партиклов

ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));			
	SetRootComponent(Collision);

	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Что бы реагировал только на павна
	UE_LOG(LogTemp, Log, TEXT("SpawnBonus"));
	Collision->SetSphereRadius(50);		// Радиус коллизии
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)		// При пересечении с бонусом
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;					// Если персонажа нет
	if (!Cast<APlayerPawn>(OtherActor)) return;	// Либо это не PlayerPawn
	BonusCollected_Implementation();
}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
	Destroy();
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float WorldMoveOffset = -300.f * DeltaTime;	 
	AddActorLocalOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}
