// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Components/SpotLightComponent.h>

#include "FollowLight.generated.h"

UCLASS()
class HANDTOHAND_API AFollowLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollowLight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
		USpotLightComponent* SpotLight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FollowActor")
		AActor* TargetFollowActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LookAtTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
