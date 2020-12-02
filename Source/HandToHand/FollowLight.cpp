// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowLight.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFollowLight::AFollowLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFollowLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFollowLight::LookAtTarget()
{

	if (IsValid(TargetFollowActor)) {

		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetFollowActor->GetActorLocation()));
	}


}

// Called every frame
void AFollowLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtTarget();

}

