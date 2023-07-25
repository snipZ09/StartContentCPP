// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StartContentCPP/Types/SpeedMode.h"
#include "StartContentCPP/Interfaces/AttackableInterface.h"
#include "CombatCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCombatComponent;
class UCollisionComponent;

class USoundCue;
class UParticleSystem;
class UAnimMontage;

UCLASS()
class STARTCONTENTCPP_API ACombatCharacter : public ACharacter, public IAttackableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UCombatComponent* GetCombat_Implementation() const;
	UCollisionComponent* GetCollision_Implementation() const;

	UFUNCTION()
	void OnHitActor(const FHitResult& HitResult);

	UFUNCTION()
	void OnReceivedPointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
	                           class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	                           const class UDamageType* DamageType, AActor* DamageCauser);

	void PlayAnimMontage(UAnimMontage* MontageToPlay);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Pressed
	UFUNCTION(BlueprintCallable)
	virtual void AttackButtonPressed();
	virtual void SprintButtonPressed();

	//Released
	virtual void SprintButtonReleased();

	//Axises
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void LookUp(float Value);
	virtual void Turn(float Value);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY()
	ESpeedMode SpeedMode;

	UPROPERTY(EditAnywhere, Category = Movement)
	float SprintSpeed = 900.f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float JogSpeed = 700.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UCollisionComponent* CollisionComponent;


	//Hitted
	UPROPERTY(EditAnywhere, Category = Hitted)
	USoundCue* HitSound;
	UPROPERTY(EditAnywhere, Category = Hitted)
	UParticleSystem* HitImpact;
	UPROPERTY(EditAnywhere, Category = Hitted)
	UAnimMontage* HitReactMontage;

	//setter getter 
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComponent; }
};
