// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include  "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"   // ��� ������
#include "Components/StaticMeshComponent.h"

// Sets default values
AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(2000.f) // ��� ����������� �������� �� ���������
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));			// ���������� ����������� �������� �������
	SetRootComponent(Collision);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);			// ������� �������� ������� ��� ������ ��� ����� ����
	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));					// ���������� ���� �������
	Mesh->SetupAttachment(RootComponent, NAME_None);									// namenone ��� �����, � �� ���� ��� ���

	//��������� �������� �������
	Mesh->SetCollisionProfileName("NoCollision");

	/*if (GetOwner())
	{
		UE_LOG(LogTemp, Log, TEXT("Proj Ovner"));
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
		
	}
	else
		UE_LOG(LogTemp, Log, TEXT("No Ovner"));*/
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();


	if (GetOwner())
	{
		
		UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();		// ������� �������� ������ �� �����������
		Collision->IgnoreComponentWhenMoving(OwnerCollision, true);								// ���������� ����
		OwnerCollision->IgnoreComponentWhenMoving(Collision, true);								// ���������� ����


		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);    // ��� ���������, ������ �������, ������� ����� ����������
	//��������� �������� �������� ������� ����
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 BodyIndex, bool Sweep, const FHitResult& Hit) // ��� ����������� ��� ����������� ������� ������� � ��� ��
{	
	if (!OtherActor || !Cast<APawn>(OtherActor)) return;		// ���� �� ������������ � ��������� ��� � ������, �� ������� �� �-��
	if (!GetOwner()) return;  // ���� �� ��� �����, �� ����������� �� �-��
	APawn* PawnOwner = Cast <APawn>(GetOwner()); // ��� �������� �� Pawn, ������ ���� �� ���������
	if(!PawnOwner) return;
	AController* Instigator1 = PawnOwner -> GetController();  // ��� ����� ������� ��� ��� ����������
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigator1,this,
	UDamageType::StaticClass()); // 1 - � ��� ������ ����������, 2 - ����, 3 - ��� ����� ���� 4 - � ����� ����� �����������, 5 -
	Destroy();
	
}



// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}


