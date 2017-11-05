// Copyright Shayne Stewart 2017


#include "TankAIController.h"

#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (ControlledTank && PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller owning %s is targeting %s"),
			*ControlledTank->GetName(),
			*PlayerTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller missing pawn or controller"))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank) {
		return Cast<ATank>(PlayerTank);
	}
	else {
		return nullptr;
	}
}

