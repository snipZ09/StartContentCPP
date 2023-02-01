// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StartContentCPP/Types/CombatState.h"
#include "CombatComponent.generated.h"

class UAnimMontage;
class ACharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARTCONTENTCPP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void RequestAttack();

	void PlayAnimMontage(UAnimMontage* MontageToPlay);

	UFUNCTION(BlueprintCallable)
	void ResetCombat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Attack();

private:
	UPROPERTY()
	ECombatState CombatState;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY()
	ACharacter* Character;

//Getter and Setter
public:	
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }
		
};
