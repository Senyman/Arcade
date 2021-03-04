// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"	
#include "Arcade/ArcadeGameMode.h"
#include "Engine/World.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));       // присваиваю коллизию корабля и называю ее pawncollision
	SetRootComponent(PawnCollision);                                                    // сделал квадратную коллизию pawncollision root компонентом
	PawnCollision -> SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));          // присваиваю тело корабля типа ustaticmeshcomponent
	PawnMesh->SetupAttachment(RootComponent);                                           // в setupattachmen мы записываем к какому родительскому компоненту мы присоединяем наш компонент (в данном случае к главному)
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);							//	Удаляю коллизию у pawnmesh

	// PawnMesh - это объект класса UStaticMeshComponent, у класса есть методы SetupAttachment, SetCollisionEnabled,
	// вызываю эти методы у объекта класса

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent1>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);	// Вначачале привизались к диспатчеру OnHealthEnded
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);			// AddDynamic значит привязаться
	// Это привязка к функции пересечения с другим объектом и при пересечениии срабатывает OnEnemyOverlap
}



void AEnemyPawn::KillPawn()		// При смерти врага
{
	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // Получает игровой режим правил для игры
	if(Gamemode) Gamemode->AddPoints(DestroyPoints);	// Если есть правила, то добавить очки
	SpawnBonuses();
	DestroyPawn();
	
}

void AEnemyPawn::SpawnBonuses()
{
	for (FBonusChance Bonus : PossibleBonuses)
	{
		FRandomStream Random; // Для рандомного спавна бонусов после смерти врага
		Random.GenerateNewSeed();
		FActorSpawnParameters SpawnParameters; // Параметры спавна, например Transform	и что б объект всегда спавнился несмотря на коллизии и ограничения
		// строчка ниже нужна , что б бонус в любом случае отспавнился без исключений
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		float RandChance = Random.RandRange(0.f, 100.f);
		UE_LOG(LogTemp, Log, TEXT(": %f"), RandChance);

		if (RandChance <= Bonus.Chance)
		{	
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
		}
	}
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor) // Это срабатывает при пересечении колизии врага со мною 
{	
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this,0)) return; // Если не пересек игрока, то выходит из ф-ии
	
	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(),this, UDamageType::StaticClass());  // наносится 100 урона
	// Записываю значение, которое нанес
	//if(AppliedDamage>0)		// Если не наносит урон, то проходит сквозь
	DestroyPawn();
}


// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float WorldMoveOffset = -300.f * DeltaTime;					// Переменная движения врага	 
	AddActorLocalOffset(FVector(WorldMoveOffset, 0.f, 0.f));	// Движение врага каждый кадр относительно мировых координат
}

