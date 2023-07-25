// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		ActorsToIgnore.Emplace(GetOwner());
	}

}


// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsEnablingCollision)
	{
		TraceCollision();
	}
}

void UCollisionComponent::EnableCollision()
{
	bIsEnablingCollision = true;
}

void UCollisionComponent::DisableCollision()
{
	bIsEnablingCollision = false;
	HittedActors.Empty();
}

void UCollisionComponent::TraceCollision()
{
	if (Character == nullptr)
	{
		return;
	}
	TArray<FHitResult> HitResults;

	FVector StartLocation = Character->GetMesh()->GetSocketLocation(StartSocketName);
	FVector EndLocation = Character->GetMesh()->GetSocketLocation(EndSocketName);

	// Start of sword -> End of Sword
	bool bHiSomething = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		Character,
		StartLocation,
		EndLocation,
		TraceRadius,
		TraceObjectTypes,
		true,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green
	);

	if (bHiSomething)
	{
		for (FHitResult HR : HitResults)
		{
			if (HR.bBlockingHit)
			{
				if (HR.GetActor())
				{
					// Lưu vào mảng Hitted Actors
					if (HittedActors.Contains(HR.GetActor()) == false)
					{
						HittedActors.Emplace(HR.GetActor());
						HitActorDelegate.Broadcast(HR);
					}
				}
			}
		}
	}
}

