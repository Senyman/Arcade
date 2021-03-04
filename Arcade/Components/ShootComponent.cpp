#include "ShootComponent.h"
#include "Engine/World.h"	// Для таймера
#include "TimerManager.h"	// Тоже для таймера

UShootComponent::UShootComponent():
	ShootPeriod(1.f)
{
}

void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	StartShooting();
}

void UShootComponent::Shoot()
{
	for (FShootInfo ShootInfo : ShootInfos)     // Цикл по всему массиву снарядов, т.е. для каждого элемента в массиве 
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();		// Я так понимаю определяем, кто будет стрелять
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
		// Это написано для того, что б acror спавнился всегда, actor может не спавниться если что-то блокирует его 
	
		// Задаю параметры сдвига снаряда (offset - смещение, сдвигаем ядра)
		FVector SpawnLocation = GetOwner()->GetActorLocation()+ShootInfo.Offset.RotateAngleAxis(GetOwner()->GetActorRotation().Yaw, FVector::UpVector); 
		//  Offset.RotateAngleAxis(GetOwner()->GetActorRotation().Yaw означает, что если я поверну корабль, то спавн снаряда тож повернет
		FRotator SpawnRotation = GetOwner()->GetActorRotation();	// Кладем в переменную поворот того, кто стреляет, т.е. точку отчета
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);				// Задает угол полета снаряда при выстреле относительно того, кто стреляет

		// Спавним сам снаряд
		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
		if(Projectile) Projectile->Damage = ShootInfo.Damage; // если снаряд отспавнился корректно, тогда ему задаем урон
	}
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
	// Устнавливаю таймер, по которому будут создаваться проджектайлы
	// ShootingTimer - я так понимаю это тип таймера
	// Далее вызываться будет фу-я Shoot
	// ShootPeriod - с какой периодичностью
	// Цикличность таймера и задержка перед первым выполнением ф-ии
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}


