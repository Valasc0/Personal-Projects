// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

#include "EnemySystem/Enemy.h"
#include "ChaosInterfaceWrapperCore.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"



// Sets default values
AFireBall::AFireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = sphereCollision;
	
	sphereCollision->InitSphereRadius(20.0f);
	sphereCollision->SetCollisionProfileName(TEXT("Trigger"));
	
	sphereCollision->OnComponentBeginOverlap.AddDynamic(this,&AFireBall::OnFireballOverlap);
	
	bCanBeReload = true;
	
	fireballNum = 1.0f;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	defaultLocation = FVector(0.0f, 0.0f, -10000000.0f);
	
	maxDistance = 30.0f;
	
	currentDistance = 0.0f;
	
	speed = 50.0f;
	
	damage = 100.0f;
	
	bIsUsable = true;
	
	cooldown = 0.0f;
	
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsUsable && bCanBeReload)
	{
		cooldown -= DeltaTime;
		if (cooldown <= 0.0f)
		{	
			fireballNum = 1.0f;
			bIsUsable = true;
			
			
		}
	}
	
	

	if (bIsSpawned)
	{
		if (currentDistance < maxDistance)
		{
			
			FireBallMove(lookVector, DeltaTime, GetActorLocation());
		}else if (currentDistance >= maxDistance)
		{
			bIsSpawned = false;
			currentDistance = 0.0f;
			
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			
			SetActorLocation(defaultLocation);
		}
		
	}
}

void AFireBall::FireballSpawn(FVector spawnLocation)
{
	
	if (!bIsSpawned && bIsUsable)
	{
		bIsUsable = false;
		
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		
		SetActorLocation(spawnLocation);
		
		bIsSpawned = true;
		
		fireballNum = 0.0f;
		
		
	}
}

void AFireBall::FireBallMove(FVector LookVector ,float DeltaTime,FVector spawnLocation)
{
	currentDistance += speed * DeltaTime;
	
	MoveLocation = LookVector * maxDistance + spawnLocation;

	MovingDirection = MoveLocation - spawnLocation;
	
	SetActorLocation(GetActorLocation() + MovingDirection * speed * DeltaTime);
}

void AFireBall::OnFireballOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	currentDistance = 0;
	if (!bIsSpawned || OtherActor == nullptr || OtherActor == this || OtherActor == GetOwner())
	{
		return;
	}
	
	FireballDamage(OtherActor);
	
	bIsSpawned = false;
	currentDistance = 0.0f;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorLocation(defaultLocation);
}

void AFireBall::FireballDamage(AActor* HitActor)
{
	if (HitActor)
	{
		AController* Player = GetInstigator() ? GetInstigator()->GetController() : nullptr;
		
		UGameplayStatics::ApplyDamage(
			HitActor,
			damage,
			Player,
			this,
			UDamageType::StaticClass()
			);
	}
	
}




 
