// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABoss::ABoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	currentspeed = 100;
	damage = 100;
	
	maxHealth = 1000;
	currentHealth = maxHealth;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Spin(DeltaTime);
}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABoss::Spin(float DeltaTime)
{		
	FRotator rotation = GetActorRotation();
	
	rotation.Yaw += currentspeed * DeltaTime;
	
	SetActorRotation(rotation );
}

void ABoss::OnBossOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GiveDamage(OtherActor);
}

void ABoss::GiveDamage(AActor* HitActor)
{
	if (HitActor)
	{
		AController* player = GetInstigator() ? GetInstigator()->GetController() : nullptr;
		
		UGameplayStatics::ApplyDamage(
			HitActor,
			damage,
			player,
			this,
			UDamageType::StaticClass());
	}
	
	
}

float ABoss::TakeDamage(float damageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(damageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	currentHealth -= ActualDamage;
	
	if (currentHealth <= 0)
	{
		Destroy();
	}
	return ActualDamage;
}