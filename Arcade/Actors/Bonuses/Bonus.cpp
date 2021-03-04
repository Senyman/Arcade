#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"			// Что бы партиклы проигрывались

ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));			
	SetRootComponent(Collision);
	//Collision->SetCollisionObjectType(ECC_WorldDynamic); // Устанавливаю тип коллизии
	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore); // Будем игнорировать все кроме одного канала

	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Что бы реагировал только на павна
	UE_LOG(LogTemp, Log, TEXT("SpawnBonus"));
	Collision->SetSphereRadius(50);		// Устанавливаем радиус коллизии
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)		// При пересечении с бонусом
{
	Super::NotifyActorEndOverlap(OtherActor);	// На всякий случай

	if (!OtherActor) return;					// Если персонажа нет, либо удален
	if (!Cast<APlayerPawn>(OtherActor)) return;	// Либо это не PlayerPawn, то выходим из ф-ии
	// А если объект есть и это PlayerPawn
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
	float WorldMoveOffset = -300.f * DeltaTime;					// Переменная движения врага	 
	AddActorLocalOffset(FVector(WorldMoveOffset, 0.f, 0.f));	// Движение врага каждый кадр относительно мировых координат
}
