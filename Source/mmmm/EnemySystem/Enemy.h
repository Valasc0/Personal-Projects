// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "PlayerAttack/FireBall.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class MMMM_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
	

public:
	// Sets default values for this actor's properties
	AEnemy();
	
	
	
	
	
	
	
	UPROPERTY(BlueprintReadOnly, Category = "Enemy_Health")
	float currentHealth;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Health")
	float maxHealth;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Stats")
	float enemySpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy_Behavior")
	bool bIsSeeing;

	
	AFireBall* enemyFireballRef;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Enemy_Behavior")
	void FollowPlayer(AActor* player, float deltaTime);
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Enemy_Behavior")
	void LookPlayer(AActor* player, float deltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "Enemy_Stats")
	float TakeDamage(float damageAmount,FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable, Category = "Enemy_Behavior")
	void EnemyAttack();
	
};
