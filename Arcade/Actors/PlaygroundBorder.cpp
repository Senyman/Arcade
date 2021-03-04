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
	if (Cast<APlayerPawn>(OtherActor)) return;		// Если каст на APlayerPawn проходит, то не выполняем дальнейшую логику
	if (Cast<ABonusSlowDownTime3>(OtherActor)) return;		// Если каст на бонус замедления времени проходит, то выходим из функции
	// Это нужно, т.к. корабль удаляется полностью, если сталкивается с врагом
	// Т.к. у него в PlayerPawn SetActorCollision false, не знаю почему это так, но как факт нужно принять
	// UE_LOG(LogTemp, Log, TEXT("OUT OF PLAYGROUND: %s"), *OtherActor->GetName());
	OtherActor->Destroy();	// Удалить объект при выходе за пределы тригера
}