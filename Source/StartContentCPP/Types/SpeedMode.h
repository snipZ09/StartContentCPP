#pragma once

UENUM(BlueprintType)
enum class ESpeedMode : uint8
{
	ESM_Jog UMETA(DisplayName = "Jog"),
	ESM_Sprint UMETA(DisplayName = "Sprint"),
	ESM_Max UMETA(DisplayName = "Max")
};