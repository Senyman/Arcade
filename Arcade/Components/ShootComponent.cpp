#include "ShootComponent.h"
#include "Engine/World.h"	// ��� �������
#include "TimerManager.h"	// ���� ��� �������

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
	for (FShootInfo ShootInfo : ShootInfos)     // ���� �� ����� ������� ��������, �.�. ��� ������� �������� � ������� 
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();		// � ��� ������� ����������, ��� ����� ��������
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
		// ��� �������� ��� ����, ��� � acror ��������� ������, actor ����� �� ���������� ���� ���-�� ��������� ��� 
	
		// ����� ��������� ������ ������� (offset - ��������, �������� ����)
		FVector SpawnLocation = GetOwner()->GetActorLocation()+ShootInfo.Offset.RotateAngleAxis(GetOwner()->GetActorRotation().Yaw, FVector::UpVector); 
		//  Offset.RotateAngleAxis(GetOwner()->GetActorRotation().Yaw ��������, ��� ���� � ������� �������, �� ����� ������� ��� ��������
		FRotator SpawnRotation = GetOwner()->GetActorRotation();	// ������ � ���������� ������� ����, ��� ��������, �.�. ����� ������
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);				// ������ ���� ������ ������� ��� �������� ������������ ����, ��� ��������

		// ������� ��� ������
		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
		if(Projectile) Projectile->Damage = ShootInfo.Damage; // ���� ������ ����������� ���������, ����� ��� ������ ����
	}
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
	// ����������� ������, �� �������� ����� ����������� ������������
	// ShootingTimer - � ��� ������� ��� ��� �������
	// ����� ���������� ����� ��-� Shoot
	// ShootPeriod - � ����� ��������������
	// ����������� ������� � �������� ����� ������ ����������� �-��
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}


