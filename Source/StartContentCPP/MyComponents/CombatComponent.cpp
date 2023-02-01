// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatState = ECombatState::ECS_Free;
	
}

void UCombatComponent::RequestAttack()
{
	if(CombatState == ECombatState::ECS_Free && AttackAnimMontages.IsEmpty() == false)
	{
		Attack();
	}
}

void UCombatComponent::Attack()
{
	UAnimMontage* MontageToPlay = AttackAnimMontages[0];
	if(MontageToPlay)
	{
		PlayAnimMontage(MontageToPlay);
		CombatState = ECombatState::ECS_Attacking;
	}
}

void UCombatComponent::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	if(Character == nullptr)
	{
		return;
	}
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if(AnimInstance && MontageToPlay)
	{
		AnimInstance->Montage_Play(MontageToPlay);
	}
}
