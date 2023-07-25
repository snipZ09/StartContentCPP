// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StartContentCPP/MyComponents/CombatComponent.h"
#include "StartContentCPP/MyComponents/CollisionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Camera Boom
	//CreateDefaultSubobject<sub obj thuộc class nào>(Text tên của CameraBoom hiện trên editor)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	//FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Character Configs
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.7f;
	GetCharacterMovement()->AirControl = 0.35f;

	//Components
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComponent"));
}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//BindAction (Tên action trong setting, event nhấn hay thả, đối tượng liên hệ event, reference của func sẽ thực hiện)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACombatCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACombatCharacter::SprintButtonPressed);

	//Release
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACombatCharacter::SprintButtonReleased);


	//BindAxis (Tên axis trong setting, đối tượng liên hệ, ref của func sẽ thực hiện)
	PlayerInputComponent->BindAxis("MoveForward", this, &ACombatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACombatCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACombatCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ACombatCharacter::Turn);
}

void ACombatCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CombatComponent)
	{
		CombatComponent->SetCharacter(this);
	}
	if (CollisionComponent)
	{
		CollisionComponent->SetCharacter(this);
		CollisionComponent->HitActorDelegate.AddDynamic(this, &ACombatCharacter::OnHitActor);
	}
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	OnTakePointDamage.AddDynamic(this, &ACombatCharacter::OnReceivedPointDamage);

}

UCombatComponent* ACombatCharacter::GetCombat_Implementation() const
{
	return CombatComponent;
}

UCollisionComponent* ACombatCharacter::GetCollision_Implementation() const
{
	return CollisionComponent;
}

// Event fire when you hit something
void ACombatCharacter::OnHitActor(const FHitResult& HitResult)
{
	AActor* HittedActor = HitResult.GetActor();
	if (HittedActor)
	{
		// Apply Damage to Actor
		UGameplayStatics::ApplyPointDamage(
			HittedActor,
			20.f,
			GetActorForwardVector(),
			HitResult,
			GetController(),
			this,
			UDamageType::StaticClass()
		);
	}
}

void ACombatCharacter::OnReceivedPointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
	                           class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	                           const class UDamageType* DamageType, AActor* DamageCauser)
{
	// Sound
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, HitLocation);
	// Spawn blood
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpact, HitLocation, FRotator());
	// Play hitted animation
	PlayAnimMontage(HitReactMontage);
	// Change combat state
	CombatComponent->SetCombatState(ECombatState::ECS_Hitted);
}

// Event fire when someone hit you
void ACombatCharacter::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && MontageToPlay)
	{
		AnimInstance->Montage_Play(MontageToPlay);
	}
}

void ACombatCharacter::AttackButtonPressed()
{
	CombatComponent->RequestAttack();
}

void ACombatCharacter::SprintButtonPressed()
{
	SpeedMode = ESpeedMode::ESM_Sprint;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACombatCharacter::SprintButtonReleased()
{
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void ACombatCharacter::MoveForward(float Value)
{
	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACombatCharacter::MoveRight(float Value)
{
	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACombatCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACombatCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}



