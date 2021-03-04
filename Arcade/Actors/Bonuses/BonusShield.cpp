#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Engine/World.h"			// ��� �������
#include "Arcade/Actors/Other/PawnShield1.h"


void ABonusShield::BonusCollected_Implementation()		// ����� ���� �����
{

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);	// ������ �� ������
	if (!PlayerPawn || !PlayerPawn->bCanBeDamaged) return;
	Super::BonusCollected_Implementation(); // ��� �� ��������� ������������ ������ �� Bonus

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// ��� ������� � ������������ ������� � ���-�� ��� ������
	// ������ � ����� ������ �����������

	APawnShield1* Shield = GetWorld()->SpawnActor<APawnShield1>(ShieldClass, SpawnParams);	// �����, ������� � ���� ��������
	// SpawnParams �������� �� ����� ������

	if(Shield) Shield->ActivateShield(PlayerPawn);		// ������� ��� ��� PlayerPawn

	

}