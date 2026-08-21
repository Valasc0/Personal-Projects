// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class MMMM_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Boss")
	float currentHealth;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Boss")
	float currentspeed;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Boss")
	float maxHealth;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Boss")
	float maxSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Boss")
	float acceleration;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Boss")
	float damage;
public:
	
	UFUNCTION(BlueprintCallable, Category = "Boss")
	void OnBossOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, 
						UPrimitiveComponent* OtherOverlappedComponent,int32 OtherBodyIndex,bool bFromSweep,
						const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Boss")
	float TakeDamage(float damageAmount,FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable, Category = "Boss")
	void GiveDamage(AActor* HitActor);
	
	UFUNCTION(BlueprintCallable, Category = "Boss")
	void Spin(float DeltaTime);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
