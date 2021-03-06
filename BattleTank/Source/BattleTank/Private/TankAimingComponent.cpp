// Copyright Shayne Stewart 2017

#include "TankAimingComponent.h"
#include "Engine.h"
#include "Tank.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting Barrel"))
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FString OurTankName = GetOwner()->GetName();
	FString HitLocationString = HitLocation.ToString();
	FString BarrelLocation = "";
	if (Barrel) { BarrelLocation = Barrel->GetComponentLocation().ToString(); }
	else { BarrelLocation = ""; }
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocationString, *BarrelLocation);
}

