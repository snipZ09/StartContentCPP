// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StartContentCPP/MyComponents/CombatComponent.h"

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

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
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



