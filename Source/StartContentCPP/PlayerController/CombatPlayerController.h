#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatPlayerController.generated.h"

class ACombatHUD;
UCLASS()
class STARTCONTENTCPP_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateCombatWidget();
	void AddCombatWidgetToViewport();

protected:
	virtual void BeginPlay() override;

private:
	// HUD
	UPROPERTY()
	ACombatHUD* CombatHUD;
};
