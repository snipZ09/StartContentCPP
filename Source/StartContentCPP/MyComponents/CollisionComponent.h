// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionComponent.generated.h"

class ACharacter;
class AActors;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARTCONTENTCPP_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void EnableCollision();

	UFUNCTION(BlueprintCallable)
	void DisableCollision();

	UFUNCTION(BlueprintCallable)
	void TraceCollision();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ACharacter* Character;

	bool bIsEnablingCollision = false;

	UPROPERTY(EditAnywhere)
	FName StartSocketName;
	UPROPERTY(EditAnywhere)
	FName EndSocketName;

	UPROPERTY(EditAnywhere)
	float TraceRadius = 20.f;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActorsToIgnore;

public:	
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }

		
};
