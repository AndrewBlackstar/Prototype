// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Character.h"
#include "Game_Prototype/Game_Prototype.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapons/GP_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"
#include "Components/GP_HealthComponent.h"
#include "Core/GP_GameMode.h"

// Sets default values
AGP_Character::AGP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FpsCameraSocketName = "SCK_Eyes_Position";
	MeleeSocketName = "SCK_Melee";
	bUseFirstPersonView = true;
	DashDistance = 2000.0f;
	MeleeDamage = 10.0f;
	MaxNumComboMultiplier = 4.0f;
	CurrentCombomultiplier = 1.5f;
	
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS camera"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FpsCameraSocketName);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;


	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS camera"));
	TPSCameraComponent->bUsePawnControlRotation = false;
	TPSCameraComponent->SetupAttachment(CameraBoom);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Melee detector"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	HealthComponent = CreateDefaultSubobject<UGP_HealthComponent>(TEXT("Health component"));

}

// Called when the game starts or when spawned
void AGP_Character::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	
		CreateInitialWeapon();
		InitalizeReferences();

		MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AGP_Character::MakeMeleeDamage);

		HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AGP_Character::OnHealthChange);
}

void AGP_Character::InitalizeReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}

	GameModeRef = Cast<AGP_GameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void AGP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGP_Character::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGP_Character::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGP_Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGP_Character::Look);
		
		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AGP_Character::Dash);

		//fire
		EnhancedInputComponent->BindAction(WeaponAction, ETriggerEvent::Started, this, &AGP_Character::StartWeaponAction);
		EnhancedInputComponent->BindAction(WeaponAction, ETriggerEvent::Completed, this, &AGP_Character::StopWeaponAction);

		//melee
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &AGP_Character::startMelee);
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Completed, this, &AGP_Character::stopMelee);

	}

}

void AGP_Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGP_Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Añadir input de yaw al controller
		AddControllerYawInput(LookAxisVector.X);

		// Invertir el valor del pitch solo si la inversión está habilitada
		float PitchInput = bIsLookInversion ? -LookAxisVector.Y : LookAxisVector.Y;
		AddControllerPitchInput(PitchInput);
	}
}

void AGP_Character::Jump()
{
	Super::Jump();
}

void AGP_Character::StopJumping()
{
	Super::StopJumping();
}

void AGP_Character::Dash()
{
	FVector DashDirection = GetVelocity().IsZero() ? GetActorForwardVector() : GetVelocity().GetSafeNormal();
	DashDirection.Z = 0; // Asegurar que no hay movimiento vertical

	// Aplica el impulso del dash
	LaunchCharacter(DashDirection * DashDistance, true, false);

}

void AGP_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AGP_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AGP_Character::StartWeaponAction()
{
	if (!bcanUseWeapon)
	{
		return;
	}
	if (CurrentWeapon)
	{
		CurrentWeapon->startAction();
	}
}

void AGP_Character::StopWeaponAction()
{
	if (!bcanUseWeapon)
	{
		return;
	}
	if (CurrentWeapon)
	{
		CurrentWeapon->stopAction();
	}
}

void AGP_Character::startMelee()
{ 
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnable)
			{
				if (CurrentCombomultiplier < MaxNumComboMultiplier)
				{
					CurrentCombomultiplier++;
					setComboEnable(false);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	if (IsValid(MyAnimInstance) && IsValid(MeleeMontaage))
	{
		MyAnimInstance->Montage_Play(MeleeMontaage);
	}
	SetMeleeState(true);
}

void AGP_Character::stopMelee()
{
}

void AGP_Character::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentCombomultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
	}
}

void AGP_Character::OnHealthChange(UGP_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (IsValid(GameModeRef))
		{
			GameModeRef->GameOver(this);
		}
	}
}

FVector AGP_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void AGP_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool AGP_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void AGP_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void AGP_Character::SetMeleeState(bool NewState)
{
	bIsDoingMelee = NewState;
	bcanUseWeapon = !NewState;
}

void AGP_Character::setComboEnable(bool NewState)
{
	bIsComboEnable = NewState;
}

void AGP_Character::ResetCombo()
{
	setComboEnable(false);
	CurrentCombomultiplier = 1.0f;
}
