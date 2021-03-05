#include "ArcadeGameMode.h"
#include "Engine/World.h"	// Для таймера
#include "TimerManager.h"	// Тоже для таймера
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Pawns/PlayerPawn.h"

AArcadeGameMode::AArcadeGameMode()	// Конструктор
	:PlayerRecoverTime(1.5f),
	CurrentShootLevel(-1),
	IncreaseDifficultyPeriod(4)
{
	EnemySpawnController1 = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController1"));
	HealthsComponent1 = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeGameMode::BeginPlay()		// Вначале привязываюсь к HealthComponent
{
	Super::BeginPlay();					// Что бы компоненты инициализировались
	HealthsComponent1->HealthsEnded.AddDynamic(this, &AArcadeGameMode::EndGame);

	PlayerPawn = Cast <APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeGameMode::ExplodePawn);
	if (!PlayerPawn) return;
	ChangeShootLevel(true);
	// PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[0].ShootInfos;		// При начале игры ставим 1 уровень

	// UGameplayStatics::GetPlayerPawn(this, 0); // Индекс игрока и от какого компонента вызываем, что бы получить GetWorld

	GetWorld()->GetTimerManager().SetTimer(IncreaceDifficultyTimer, this, &AArcadeGameMode::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
	// Включаю таймер, что б ускорялся спавн врагов
}

void AArcadeGameMode::ExplodePawn_Implementation() // Вызывается, когда персонажу наносят урон
{
	PlayerPawn->ExplodePawn();		 
	HealthsComponent1->ChangeHealths(-1); // Отнимаем 1 хп
	ChangeShootLevel(false);
	if(!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeGameMode::RecoverPawn, PlayerRecoverTime, false);
	// Устанавливаем таймер, после которого воскреситься корабль
}

void AArcadeGameMode::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}


void AArcadeGameMode::EndGame()
{
	IsGameOver = true;

	EnemySpawnController1->SetActive(false); // Вызовет в EnemySpawnController ф-ю Deactivate
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AArcadeGameMode::IncreaseDifficulty()
{
	EnemySpawnController1->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController1->ChangeStageTimeMultiplier * 0.95,0.4);
	UE_LOG(LogTemp, Warning, TEXT("Difficulty increased %f"), EnemySpawnController1->ChangeStageTimeMultiplier);
	// Устанавливаю таймер на максимальное значение между двух либо то которое было, либо 0,4
}

void AArcadeGameMode::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AArcadeGameMode::ChangeShootLevel(bool Up)		// Изменение уровня игрока и соответственно типа стрельбы
{
	PlayerPawn = Cast <APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel =  FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1),0,ShootInfoLevels.Num()-1); // Если Up правда, то выбирается 1, в инном случае выбирается -1
	if (NewLevel == CurrentShootLevel) return false;	// Если значение уровня не изменилось то возвращаем false и не меняем уровень

	CurrentShootLevel = NewLevel;
	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	PlayerPawn->ShootComponent->StopShooting();
	PlayerPawn->ShootComponent->StartShooting();
	return true;
}

