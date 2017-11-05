// Copyright Shayne Stewart 2017

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Controller owns %s"), *ControlledTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Controller missing pawn"))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

