// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerPawn.h"							// header файл моего класса, всегда должен быть первым
#include "Components/StaticMeshComponent.h"		// для того что б тело корабля могло по прикрепиться к root component
#include "Components/InputComponent.h"			// библиотека для управления кораблем
#include "GameFramework/Actor.h"	
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"		//библиотека для player controller
#include "Kismet/GameplayStatics.h"


APlayerPawn::APlayerPawn()						// Это конструктор класса
	:
	TouchMoveSensivity(3.f),
	MoveLimit(FVector2D(1000.f, 1000.f)),
	NumberOfMaterial(0)
{
	
	PrimaryActorTick.bCanEverTick = true;                                              // set this pawn to call tick() every frame.  you can turn this off to improve performance if you don't need it.


	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));       // создаю коллизию корабля через CreateDefaultSubobject
	SetRootComponent(PawnCollision);                                                    // SetRootComponent - функция, сделал коллизию root компонентом
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);	// Что бы игнорировал физические объекты

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));          // создаю меш (тело) корабля
	PawnMesh->SetupAttachment(RootComponent);                                           // присоединяю меш к Root компоненту

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));          // создаю камеру
	

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));			// присваиваю шут компоненту тип

}


void APlayerPawn::PossessedBy(AController* newcontroller)
{
	PlayerController = Cast<APlayerController>(newcontroller);  //делаем каст на player controller, getcontroller() - ссылка на объект, которы я пытаюсь сделать каст
	// PlayerController->bShowMouseCursor = true;																		  // делаю контроллера своим playercontroller
}



// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	// UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	PawnMesh->GetMaterial(0);
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) 
{
	if (!CanBeDamaged()) return 0.f;
		Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser); // Нужен для вызова родительской логики
		PawnDamaged.Broadcast();
		// Если не будет супера, то не будет вызываться диспатчер
		// UE_LOG(LogTemp, Log, TEXT("PlayerDamaged"));
		return Damage;
}


bool APlayerPawn::CanBeDamaged_Implementation()
{
	return bCanBeDamaged;
}

void APlayerPawn::ExplodePawn_Implementation()	
{
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Cast<UParticleSystemComponent>(Component)->Deactivate();
	}
	SetActorEnableCollision(false);	// Отключаем коллизию после уничтожения корабля
	
	ShootComponent->StopShooting();	// Прекращаем стрельбу на время пока ранен

	
	
	for (NumberOfMaterial; NumberOfMaterial < 7; NumberOfMaterial++)
	{
		PawnMesh->SetMaterial(NumberOfMaterial, RecoverMaterial);
	}
	
	NumberOfMaterial = 0;

	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);		// Спавнит партикл при уничтожении корабля
	
	
}

void APlayerPawn::RecoverPawn_Implementation()
{
	ShootComponent->StartShooting();
	SetActorEnableCollision(true);	// Включаем коллизию после возрождения корабля


	while (NumberOfMaterial < 7)
	{
		PawnMesh->SetMaterial(NumberOfMaterial, PawnMaterial);			// Устанавливем оригинальный материал, после полного воскрешения
		NumberOfMaterial++;
	}
	NumberOfMaterial = 0;

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Cast<UParticleSystemComponent>(Component)->Activate(true);
	}
}



void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	// IE_Pressed - enum - перечисление - IE_Pressed - когда мы нажимаем
	// APlayerPawn::OnTouchPress - это функция, которую нужно будет создать
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);	
	
	// IE_Repeat означает, что функция OnTouchMove будет выпонятся пока ЛКМ нажата 


	// einputevent - это перечисление, ie_pressed - когда мы нажимаем, this - ссылка на объект в котором мы вызываем действие при нажатии(аналог self в bp)
	// дальше необходимо вставить ссыку на функцию, которую нужно создать отдельно, она будет выполняться при нажатии на кнопку. также нужно,  
	//что б в ontouchpress были такие же параметры как и в bindtouch, поэтому в функции нужно все их создать
}



void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)  // FVector - это 3д вектор, создаем параметры для ф-ии ontouchmove
{																			  
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);			// delta - это расстояние между точкой где курсор и местом,
																												// где курсор был в прошлый раз (разница между кадрами в движении мышки)

	TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity; 

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);  // Ограничения по x и y
	NewLocation.Y = FMath::Clamp(NewLocation.Y - TouchDeltaMove.X, -MoveLimit.X, MoveLimit.X);	
	
	// NewLocation.X - Это координаты корабля по x, TouchDeltaMove.Y - Это координаты тоже по оси x, только в экранных коодинатах это y

	SetActorLocation(NewLocation); // Устанавливает ator на координаты NewLocation
	

	TouchLocation = FVector2D(Location.X, Location.Y);	// Х и У подхватывется не от той точки, которую отпустили
}


void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)		// в 2д вектор передаются параметры из 3д вектора 
{
	UE_LOG(LogTemp, Warning, TEXT("touch press: %s"), *TouchLocation.ToString()); // %s значит вывести стринг %f - float
	TouchLocation = FVector2D (Location.X, Location.Y);								
	// Это нужно, что бы записать коодинаты нажатия, для того что б записывалось движение относительно точки нажатия 
}


