// Copyright Epic Games, Inc. All Rights Reserved.

#include "mmmmCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "PlayerAttack/FireBall.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "mmmm.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"

AmmmmCharacter::AmmmmCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Fireball variables
	pushPower = 1000.0f;
	
	maxHeal = 1000.0f;
	currentHeal = maxHeal;
	
}

void AmmmmCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	
	if (GetWorld() && fireBallClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		fireBallref = GetWorld()->SpawnActor<AFireBall>(fireBallClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
}

void AmmmmCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AmmmmCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AmmmmCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AmmmmCharacter::Look);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AmmmmCharacter::Attack);
	}
	else
	{
		UE_LOG(Logmmmm, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AmmmmCharacter::Tick(float DeltaTime)
{
	if (GetCharacterMovement()->IsFalling())
	{
		fireBallref->bCanBeReload= false;
	}
	else
	{
		fireBallref->bCanBeReload= true;
	}
	
}

void AmmmmCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AmmmmCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AmmmmCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AmmmmCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AmmmmCharacter::DoJumpStart()
{
	
	Jump();
	
}

void AmmmmCharacter::DoJumpEnd()
{
	
	StopJumping();
	
}

void AmmmmCharacter::Attack(const FInputActionValue& Value)
{
	// input is a boolean
	bool bPressed = Value.Get<bool>();
	
	
	
	
	
	
	if (bPressed && fireBallClass && fireBallref->fireballNum != 0)
	{
		spawnLocation = GetActorLocation();
		
		fireBallref->lookVector = GetFollowCamera()->GetForwardVector();
		
		fireBallref->FireballSpawn(spawnLocation);
		
		
		
		USkeletalMeshComponent* characterMesh = GetMesh();
		
		if (characterMesh != nullptr)
		{
			UAnimInstance* AnimInstance = characterMesh->GetAnimInstance();
			
			AnimInstance->Montage_Play(AttackMontage,1.0f);
		}
		if (fireBallref->bIsSpawned == true && fireBallref->bIsUsable == false)
		{
			FVector Playerpush = GetFollowCamera()->GetForwardVector() * -1 * pushPower;
			LaunchCharacter(Playerpush,true,true);
		}
		
		
	}
}

float AmmmmCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	currentHeal -= ActualDamage;
	
	if (currentHeal <= 0)
	{
		Destroy();
	}
	return ActualDamage;
	
}

	


