#include "BonusPoints3.h"
#include "Kismet/GameplayStatics.h"		// ������ ����� ����� ������ �� ������� ����� � ���������
#include "Arcade/ArcadeGameMode.h"

void ABonusPoints3::BonusCollected_Implementation()		// ����� ���� �����
{

	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // �������� ������� ����� ������ ��� ����
	if (Gamemode) Gamemode->AddPoints(Points);	// ���� ���� �������, �� �������� ����
	Destroy();

	Super::BonusCollected_Implementation(); // ��� �� ��������� ������������ ������ �� Bonus
	
}