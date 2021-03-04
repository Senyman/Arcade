// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerPawn.h"							// header ���� ����� ������, ������ ������ ���� ������
#include "Components/StaticMeshComponent.h"		// ��� ���� ��� � ���� ������� ����� �� ������������ � root component
#include "Components/InputComponent.h"			// ���������� ��� ���������� ��������
#include "GameFramework/Actor.h"	
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"		//���������� ��� player controller
#include "Kismet/GameplayStatics.h"


APlayerPawn::APlayerPawn()						// ��� ����������� ������
	:
	TouchMoveSensivity(3.f),
	MoveLimit(FVector2D(1000.f, 1000.f)),
	NumberOfMaterial(0)
{
	
	PrimaryActorTick.bCanEverTick = true;                                              // set this pawn to call tick() every frame.  you can turn this off to improve performance if you don't need it.


	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));       // ������ �������� ������� ����� CreateDefaultSubobject
	SetRootComponent(PawnCollision);                                                    // SetRootComponent - �������, ������ �������� root �����������
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);	// ��� �� ����������� ���������� �������

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));          // ������ ��� (����) �������
	PawnMesh->SetupAttachment(RootComponent);                                           // ����������� ��� � Root ����������

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));          // ������ ������
	

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));			// ���������� ��� ���������� ���

}


void APlayerPawn::PossessedBy(AController* newcontroller)
{
	PlayerController = Cast<APlayerController>(newcontroller);  //������ ���� �� player controller, getcontroller() - ������ �� ������, ������ � ������� ������� ����
	// PlayerController->bShowMouseCursor = true;																		  // ����� ����������� ����� playercontroller
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
		Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser); // ����� ��� ������ ������������ ������
		PawnDamaged.Broadcast();
		// ���� �� ����� ������, �� �� ����� ���������� ���������
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
	SetActorEnableCollision(false);	// ��������� �������� ����� ����������� �������
	
	ShootComponent->StopShooting();	// ���������� �������� �� ����� ���� �����

	
	
	for (NumberOfMaterial; NumberOfMaterial < 7; NumberOfMaterial++)
	{
		PawnMesh->SetMaterial(NumberOfMaterial, RecoverMaterial);
	}
	
	NumberOfMaterial = 0;

	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);		// ������� ������� ��� ����������� �������
	
	
}

void APlayerPawn::RecoverPawn_Implementation()
{
	ShootComponent->StartShooting();
	SetActorEnableCollision(true);	// �������� �������� ����� ����������� �������


	while (NumberOfMaterial < 7)
	{
		PawnMesh->SetMaterial(NumberOfMaterial, PawnMaterial);			// ������������ ������������ ��������, ����� ������� �����������
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
	// IE_Pressed - enum - ������������ - IE_Pressed - ����� �� ��������
	// APlayerPawn::OnTouchPress - ��� �������, ������� ����� ����� �������
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);	
	
	// IE_Repeat ��������, ��� ������� OnTouchMove ����� ��������� ���� ��� ������ 


	// einputevent - ��� ������������, ie_pressed - ����� �� ��������, this - ������ �� ������ � ������� �� �������� �������� ��� �������(������ self � bp)
	// ������ ���������� �������� ����� �� �������, ������� ����� ������� ��������, ��� ����� ����������� ��� ������� �� ������. ����� �����,  
	//��� � � ontouchpress ���� ����� �� ��������� ��� � � bindtouch, ������� � ������� ����� ��� �� �������
}



void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)  // FVector - ��� 3� ������, ������� ��������� ��� �-�� ontouchmove
{																			  
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);			// delta - ��� ���������� ����� ������ ��� ������ � ������,
																												// ��� ������ ��� � ������� ��� (������� ����� ������� � �������� �����)

	TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity; 

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);  // ����������� �� x � y
	NewLocation.Y = FMath::Clamp(NewLocation.Y - TouchDeltaMove.X, -MoveLimit.X, MoveLimit.X);	
	
	// NewLocation.X - ��� ���������� ������� �� x, TouchDeltaMove.Y - ��� ���������� ���� �� ��� x, ������ � �������� ���������� ��� y

	SetActorLocation(NewLocation); // ������������� ator �� ���������� NewLocation
	

	TouchLocation = FVector2D(Location.X, Location.Y);	// � � � ������������� �� �� ��� �����, ������� ���������
}


void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)		// � 2� ������ ���������� ��������� �� 3� ������� 
{
	UE_LOG(LogTemp, Warning, TEXT("touch press: %s"), *TouchLocation.ToString()); // %s ������ ������� ������ %f - float
	TouchLocation = FVector2D (Location.X, Location.Y);								
	// ��� �����, ��� �� �������� ��������� �������, ��� ���� ��� � ������������ �������� ������������ ����� ������� 
}


