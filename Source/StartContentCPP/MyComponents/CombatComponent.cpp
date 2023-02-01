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

	ResetCombat();
}

void UCombatComponent::RequestAttack()
{
	if(CanAttack())
	{
		bIsReachedContinueAttackPoint = false;
		Attack();
	}
}

bool UCombatComponent::CanAttack()
{
	bool bDesiredCombatState = CombatState == ECombatState::ECS_Free \
	|| (bIsReachedContinueAttackPoint && CombatState == ECombatState::ECS_Attacking);
	return bDesiredCombatState
	&& AttackAnimMontages.IsEmpty() == false
	;
}

void UCombatComponent::Attack()
{
	UAnimMontage* MontageToPlay = AttackAnimMontages[AttackIndex];
	if(MontageToPlay)
	{
		PlayAnimMontage(MontageToPlay);
		CombatState = ECombatState::ECS_Attacking;
		AttackIndex++;
		if(AttackIndex > AttackAnimMontages.Num() - 1)
		{
			AttackIndex = 0;
		}
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

void UCombatComponent::ResetCombat()
{
	CombatState = ECombatState::ECS_Free;
	AttackIndex = 0;
	bIsReachedContinueAttackPoint = false;
}

void UCombatComponent::ContinueCombo()
{
	bIsReachedContinueAttackPoint = true;
}
