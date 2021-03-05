#include "Arcade/Actors/Bonuses/BonusShootLevelUP.h"
#include "Kismet/GameplayStatics.h"		// ������ ����� ����� ������ �� ������� ����� � ���������
#include "Arcade/ArcadeGameMode.h"

void ABonusShootLevelUP::BonusCollected_Implementation()		// ����� ���� �����
{
	AArcadeGameMode* Gamemode = Cast< AArcadeGameMode>(UGameplayStatics::GetGameMode(this)); // �������� ������� ����� ������ ��� ����
	if (!Gamemode) return;

	Gamemode->ChangeShootLevel(true);
	Super::BonusCollected_Implementation(); // ��� �� ��������� ������������ ������ �� Bonus
}