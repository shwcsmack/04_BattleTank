// Copyright Shayne Stewart 2017

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;
	
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation;

	UPROPERTY(EditAnywhere)
		int32 LineTraceRange;
};
