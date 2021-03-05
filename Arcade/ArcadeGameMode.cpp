#include "ArcadeGameMode.h"
#include "Engine/World.h"	// ��� �������
#include "TimerManager.h"	// ���� ��� �������
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Pawns/PlayerPawn.h"

AArcadeGameMode::AArcadeGameMode()	// �����������
	:PlayerRecoverTime(1.5f),
	CurrentShootLevel(-1),
	IncreaseDifficultyPeriod(4)
{
	EnemySpawnController1 = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController1"));
	HealthsComponent1 = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeGameMode::BeginPlay()		// ������� ������������ � HealthComponent
{
	Super::BeginPlay();					// ��� �� ���������� ������������������
	HealthsComponent1->HealthsEnded.AddDynamic(this, &AArcadeGameMode::EndGame);

	PlayerPawn = Cast <APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeGameMode::ExplodePawn);
	if (!PlayerPawn) return;
	ChangeShootLevel(true);
	// PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[0].ShootInfos;		// ��� ������ ���� ������ 1 �������

	// UGameplayStatics::GetPlayerPawn(this, 0); // ������ ������ � �� ������ ���������� ��������, ��� �� �������� GetWorld

	GetWorld()->GetTimerManager().SetTimer(IncreaceDifficultyTimer, this, &AArcadeGameMode::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
	// ������� ������, ��� � ��������� ����� ������
}

void AArcadeGameMode::ExplodePawn_Implementation() // ����������, ����� ��������� ������� ����
{
	PlayerPawn->ExplodePawn();		 
	HealthsComponent1->ChangeHealths(-1); // �������� 1 ��
	ChangeShootLevel(false);
	if(!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeGameMode::RecoverPawn, PlayerRecoverTime, false);
	// ������������� ������, ����� �������� ������������ �������
}

void AArcadeGameMode::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}


void AArcadeGameMode::EndGame()
{
	IsGameOver = true;

	EnemySpawnController1->SetActive(false); // ������� � EnemySpawnController �-� Deactivate
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AArcadeGameMode::IncreaseDifficulty()
{
	EnemySpawnController1->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController1->ChangeStageTimeMultiplier * 0.95,0.4);
	UE_LOG(LogTemp, Warning, TEXT("Difficulty increased %f"), EnemySpawnController1->ChangeStageTimeMultiplier);
	// ������������ ������ �� ������������ �������� ����� ���� ���� �� ������� ����, ���� 0,4
}

void AArcadeGameMode::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AArcadeGameMode::ChangeShootLevel(bool Up)		// ��������� ������ ������ � �������������� ���� ��������
{
	PlayerPawn = Cast <APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel =  FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1),0,ShootInfoLevels.Num()-1); // ���� Up ������, �� ���������� 1, � ����� ������ ���������� -1
	if (NewLevel == CurrentShootLevel) return false;	// ���� �������� ������ �� ���������� �� ���������� false � �� ������ �������

	CurrentShootLevel = NewLevel;
	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	PlayerPawn->ShootComponent->StopShooting();
	PlayerPawn->ShootComponent->StartShooting();
	return true;
}

