// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundBorder.h"
#include "Components/BoxComponent.h"
#include "Arcade/Pawns/PlayerPawn.h"
#include "Arcade/Actors/Bonuses/BonusSlowDownTime3.h"
APlaygroundBorder::APlaygroundBorder()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetCollisionProfileName("OverlapAll");
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (!OtherActor) return;
	if (Cast<APlayerPawn>(OtherActor)) return;		// ���� ���� �� APlayerPawn ��������, �� �� ��������� ���������� ������
	if (Cast<ABonusSlowDownTime3>(OtherActor)) return;		// ���� ���� �� ����� ���������� ������� ��������, �� ������� �� �������
	// ��� �����, �.�. ������� ��������� ���������, ���� ������������ � ������
	// �.�. � ���� � PlayerPawn SetActorCollision false, �� ���� ������ ��� ���, �� ��� ���� ����� �������
	// UE_LOG(LogTemp, Log, TEXT("OUT OF PLAYGROUND: %s"), *OtherActor->GetName());
	OtherActor->Destroy();	// ������� ������ ��� ������ �� ������� �������
}