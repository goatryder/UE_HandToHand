// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "CPP_Character.generated.h"


UCLASS()
class HANDTOHAND_API ACPP_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed = 75.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float FasterMovementSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DashSpeed = 225.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DashTimeSec = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DashCoolDown = 1.f;

	void MoveRight(float Val);

	void MoveFaster();
	void CancelMoveFaster();

	void Dash();
	void CancelDash();

	void Jump();
	void StopJumping();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* PunchLeftMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* PunchRightMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* KickLeftMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* KickRightMontage;

	void PunchLeft();
	void PunchRight();
	void KickLeft();
	void KickRight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCanDash = true;
	float DashTimeAccomulation;
	float CurrentMaxSpeed = MovementSpeed;

	bool bCanMove = true;

	UFUNCTION()
		void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
