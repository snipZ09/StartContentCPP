#pragma once

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_Free UMETA(DisplayName = "Free"),
	ECS_Attacking UMETA(DisplayName = "Attacking"),
	ECS_Max UMETA(DisplayName = "Max")
};