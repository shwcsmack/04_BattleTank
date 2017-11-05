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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; //Out Parameter
	
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}

	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D CrosshairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,
													ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(CrosshairScreenLocation, LookDirection))
	{
		OutHitLocation = LookDirection;
	}
	
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector Location;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		Location,
		OutLookDirection);
}

