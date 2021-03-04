// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include  "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"   // ƒл€ дамага
#include "Components/StaticMeshComponent.h"

// Sets default values
AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(2000.f) // “ак указываютс€ значени€ по умолчанию
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));			// ѕрисваиваю сферическую коллизию снар€да
	SetRootComponent(Collision);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);			// ”бираем коллизию снар€да при спавне дл€ фикса бага
	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));					// ѕрисваиваю тело снар€да
	Mesh->SetupAttachment(RootComponent, NAME_None);									// namenone это сокет, € не знаю что ето

	//отключаем коллизию снар€да
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
		
		UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();		// Ќаходим коллизию овнера по компонентам
		Collision->IgnoreComponentWhenMoving(OwnerCollision, true);								// »гнорирует себ€
		OwnerCollision->IgnoreComponentWhenMoving(Collision, true);								// »гнорирует себ€


		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);    // Ёто диспатчер, внутри функци€, котора€ будет вызыватьс€
	//ƒобавл€ет коллизию снар€дам вначале игры
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 BodyIndex, bool Sweep, const FHitResult& Hit) // Ёто срабатывает при пересечении колизии снар€да с кем то
{	
	if (!OtherActor || !Cast<APawn>(OtherActor)) return;		// ≈сли не пересекаетс€ с верктором или с пешкой, то выходит из ф-ии
	if (!GetOwner()) return;  // ≈сли не гет овнер, то возвращаюсь из ф-ии
	APawn* PawnOwner = Cast <APawn>(GetOwner()); // кто владелец из Pawn, делаем каст на персонажа
	if(!PawnOwner) return;
	AController* Instigator1 = PawnOwner -> GetController();  // гет овнер корабл€ это уже контроллер
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigator1,this,
	UDamageType::StaticClass()); // 1 - с кем снар€д столкнулс€, 2 - урон, 3 - кто нанес урон 4 - в каком файле срабатывает, 5 -
	Destroy();
	
}



// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}


