// Copyright Shayne Stewart 2017

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller owns %s"), *ControlledTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller missing pawn"))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

