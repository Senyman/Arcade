#include "PawnShield1.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Engine/World.h"	// ��� �������
#include "TimerManager.h"	// ���� ��� �������

APawnShield1::APawnShield1():
	ShieldTime(5.f)
{
}

void APawnShield1::ActivateShield(APlayerPawn* PlayerPawn) 
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}

	ShieldForPawn = PlayerPawn;
	PlayerPawn->bCanBeDamaged = false;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules  // ��� ��������� ����������, ����� ������� ������������� ��� � �������
	(
		EAttachmentRule::SnapToTarget,		// ��� ������������ �� ����������� ��������
		// �������� SnapToTarget ��������, ��� ������ ���������� � �������� ����� ����������� �� �������� ������� �� ���� ������
		// � ������ ������ ���������� ���� ����������� � ���������� PlayerPawn
		EAttachmentRule::SnapToTarget,		// ������� 
		// ��� ����� �������� ���� �� ���� � �������, �� �.�. ����� ��� �� �����������
		EAttachmentRule::KeepWorld,			// ������
		// KeepWorld ������ ��� ������� ���� ��������� ������ �� ��� � �� ������������
		false
	);		
	AttachToActor(PlayerPawn, AttachRules);	// ��������� ���� ������ � �������, � ������ ������ ��� � �������, � ����� ������� ���������� 
	// ��� � ������� ���� �-�� ����� ���������� ������ � ������ ������� �������

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield1::DeactivateShield, ShieldTime, false);
}

void APawnShield1::DeactivateShield()
{
	if (!ShieldForPawn) return;
	ShieldForPawn->bCanBeDamaged = true;
	Destroy();
}
