// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	maxHealth = 100.0f;
	
	currentHealth = maxHealth;
	
	bIsSeeing =false;
	
	
	
	enemyFireballRef = CreateDefaultSubobject<AFireBall>("Fireball");
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	
	
	Super::Tick(DeltaTime);
	FollowPlayer(GetWorld()->GetFirstPlayerController()->GetPawn() , DeltaTime);
	
	LookPlayer(GetWorld()->GetFirstPlayerController()->GetPawn() , DeltaTime);

	if (bIsSeeing)
	{
		EnemyAttack();
	}
	
}

void AEnemy::FollowPlayer(AActor* player , float  deltaTime)
{
	if (player && bIsSeeing)
	{
		FVector direction = player->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		direction.Z = 0; 
		SetActorLocation(GetActorLocation() + direction * deltaTime * enemySpeed);
	}
}


void AEnemy::LookPlayer(AActor* player, float deltaTime)
{
	if (player && bIsSeeing)
	{
		FVector direction = player->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		SetActorRotation(direction.Rotation());
	}
}

float AEnemy::TakeDamage(float damageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(damageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	currentHealth -= ActualDamage;
	
	if (currentHealth <= 0)
	{
		Destroy();
	}
	return ActualDamage;
}

void AEnemy::EnemyAttack()
{
	
	
	FVector spawnLocation = GetActorLocation();
	spawnLocation.Z += 5.0f;
	enemyFireballRef->FireballSpawn(spawnLocation);
	
	
	
}
