// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StartContentCPP/Types/SpeedMode.h"
#include "CombatCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class STARTCONTENTCPP_API ACombatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Pressed
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
//setter getter
public:	
	

	
};
