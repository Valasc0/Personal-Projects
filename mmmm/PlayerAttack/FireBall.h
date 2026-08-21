// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

UCLASS()
class MMMM_API AFireBall : public AActor
{
	GENERATED_BODY()
	
	
	
public:
	// Sets default values for this actor's properties
	AFireBall();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	FVector defaultLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	FRotator defaultRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fireball")
	FVector lookVector;
	
	UPROPERTY()
	USphereComponent* sphereCollision;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float length;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float maxDistance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fireball")
	float currentDistance;
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fireball")
	bool bIsSpawned;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fireball")
	bool bIsUsable;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Fireball")
	bool bCanBeReload;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Fireball")
	float fireballNum;
	
	
	FProperty* GetProperty(FName propertyName);
	
protected:
	FVector MoveLocation;
	
	FVector MovingDirection;
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Fireball")
	void FireballSpawn(FVector spawnLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Fireball")
	void FireBallMove(FVector PlayerForwardVector, float DeltaTime, FVector spawnLocation);
	
	UFUNCTION()
	void OnFireballOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, 
						UPrimitiveComponent* OtherOverlappedComponent,int32 OtherBodyIndex,bool bFromSweep,
						const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Fireball")
	void FireballDamage(AActor* HitActor);
	
	virtual void Tick(float DeltaTime) override;
};
