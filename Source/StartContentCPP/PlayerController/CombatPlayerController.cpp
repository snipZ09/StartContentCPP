#include "CombatPlayerController.h"
#include "StartContentCPP/HUD/CombatHUD.h"
#include "StartContentCPP/HUD/CombatWidget.h"

void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CombatHUD = Cast<ACombatHUD>(GetHUD());
}

void ACombatPlayerController::CreateCombatWidget()
{
	if (CombatHUD)
	{
		CombatHUD->CreateCombatWidget();
	}
}

void ACombatPlayerController::AddCombatWidgetToViewport()
{
	if (CombatHUD)
	{
		CombatHUD->AddWidgetToViewport(CombatHUD->GetCombatWidget());
	}
}

