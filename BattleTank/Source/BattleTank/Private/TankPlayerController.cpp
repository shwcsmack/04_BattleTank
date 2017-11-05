// Copyright Shayne Stewart 2017

#include "TankPlayerController.h"
#include "Engine/World.h"


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
	
	FVector HitLocation = FVector(0.0); //Out Parameter
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
		FVector HitLocation;
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	OutHitLocation = FVector(0.0);
	return false;
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

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult = FHitResult();
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + (LookDirection * LineTraceRange);
	FCollisionQueryParams QueryParams = FCollisionQueryParams();
	FCollisionResponseParams ResponseParams = FCollisionResponseParams();

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0.0);
	return false;
}

