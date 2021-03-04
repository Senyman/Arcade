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

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));       // ���������� �������� ������� � ������� �� pawncollision
	SetRootComponent(PawnCollision);                                                    // ������ ���������� �������� pawncollision root �����������
	PawnCollision -> SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));          // ���������� ���� ������� ���� ustaticmeshcomponent
	PawnMesh->SetupAttachment(RootComponent);                                           // � setupattachmen �� ���������� � ������ ������������� ���������� �� ������������ ��� ��������� (� ������ ������ � ��������)
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);							//	������ �������� � pawnmesh

	// PawnMesh - ��� ������ ������ UStaticMeshComponent, � ������ ���� ������ SetupAttachment, SetCollisionEnabled,
	// ������� ��� ������ � ������� ������

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent1>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);	// ��������� ����������� � ���������� OnHealthEnded
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);			// AddDynamic ������ �����������
	// ��� �������� � ������� ����������� � ������ �������� � ��� ������������ ����������� OnEnemyOverlap
}



void AEnemyPawn::KillPawn()		// ��� ������ �����
{
	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // �������� ������� ����� ������ ��� ����
	if(Gamemode) Gamemode->AddPoints(DestroyPoints);	// ���� ���� �������, �� �������� ����
	SpawnBonuses();
	DestroyPawn();
	
}

void AEnemyPawn::SpawnBonuses()
{
	for (FBonusChance Bonus : PossibleBonuses)
	{
		FRandomStream Random; // ��� ���������� ������ ������� ����� ������ �����
		Random.GenerateNewSeed();
		FActorSpawnParameters SpawnParameters; // ��������� ������, �������� Transform	� ��� � ������ ������ ��������� �������� �� �������� � �����������
		// ������� ���� ����� , ��� � ����� � ����� ������ ����������� ��� ����������
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

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor) // ��� ����������� ��� ����������� ������� ����� �� ���� 
{	
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this,0)) return; // ���� �� ������� ������, �� ������� �� �-��
	
	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(),this, UDamageType::StaticClass());  // ��������� 100 �����
	// ��������� ��������, ������� �����
	//if(AppliedDamage>0)		// ���� �� ������� ����, �� �������� ������
	DestroyPawn();
}


// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float WorldMoveOffset = -300.f * DeltaTime;					// ���������� �������� �����	 
	AddActorLocalOffset(FVector(WorldMoveOffset, 0.f, 0.f));	// �������� ����� ������ ���� ������������ ������� ���������
}

