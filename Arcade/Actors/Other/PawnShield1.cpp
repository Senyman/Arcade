#include "PawnShield1.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Engine/World.h"	// Для таймера
#include "TimerManager.h"	// Тоже для таймера

APawnShield1::APawnShield1():
	ShieldTime(5.f) {}

void APawnShield1::ActivateShield(APlayerPawn* PlayerPawn) 
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}

	ShieldForPawn = PlayerPawn;
	PlayerPawn->bCanBeDamaged = false;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules  // Эта структура определяет, каким образом прикрепляется щит к кораблю
	(
		EAttachmentRule::SnapToTarget,		// По координатам
		// SnapToTarget означает, при аттаче координаты и свойство будет скопировано от целевого объекта на этот объект
		// В данном случае координаты щита перенесутся в координаты PlayerPawn
		EAttachmentRule::SnapToTarget,		// Поворот 
		EAttachmentRule::KeepWorld,			// Размер
		false
	);		
	AttachToActor(PlayerPawn, AttachRules);	// Приатачет один объект к другому, в данном случае щит к кораблю, и каким образом приатачить 
	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield1::DeactivateShield, ShieldTime, false);
}

void APawnShield1::DeactivateShield()
{
	if (!ShieldForPawn) return;
	ShieldForPawn->bCanBeDamaged = true;
	Destroy();
}
