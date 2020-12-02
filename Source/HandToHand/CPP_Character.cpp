// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Character.h"

// Sets default values
ACPP_Character::ACPP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	DashCoolDown += DashTimeSec;

}

// Called when the game starts or when spawned
void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ACPP_Character::OnMontageEnded);

}

// Called every frame
void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// dash cooldown
	DashTimeAccomulation += DeltaTime;

	if (DashTimeAccomulation > DashCoolDown) {

		bCanDash = true;

		DashTimeAccomulation = 0.f;

	}
	//

	// print current speed
	/*
	float Speed;
	
	if (FVector::DotProduct(GetVelocity(), GetActorForwardVector()) > 0.f) {
		
		//Speed = GetVelocity().Size();
		Speed = GetVelocity().Size();

	}
	else {

		Speed = -GetVelocity().Size();

	}*/

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString::Printf(TEXT("HORIZONTAL SPEED: %f"), GetVelocity().X));
	 

}

// Called to bind functionality to input
void ACPP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ACPP_Character::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_Character::StopJumping);

	PlayerInputComponent->BindAction("MoveFaster", IE_Pressed, this, &ACPP_Character::MoveFaster);
	PlayerInputComponent->BindAction("MoveFaster", IE_Released, this, &ACPP_Character::CancelMoveFaster);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACPP_Character::Dash);
	
	PlayerInputComponent->BindAction("PunchLeft", IE_Pressed, this, &ACPP_Character::PunchLeft);
	PlayerInputComponent->BindAction("PunchRight", IE_Pressed, this, &ACPP_Character::PunchRight);
	PlayerInputComponent->BindAction("KickLeft", IE_Pressed, this, &ACPP_Character::KickLeft);
	PlayerInputComponent->BindAction("KickRight", IE_Pressed, this, &ACPP_Character::KickRight);

}

void ACPP_Character::MoveRight(float Val)
{

	if (Val == 0.f || bCanMove == false)
		return;

	FVector Right = GetActorForwardVector();

	if (FVector::DotProduct(Right, FVector::ForwardVector) < 0.f)
		Right *= -1.f;

	AddMovementInput(Right, Val);

}

void ACPP_Character::MoveFaster()
{
	
	GetCharacterMovement()->MaxWalkSpeed = FasterMovementSpeed;
	CurrentMaxSpeed = FasterMovementSpeed;
}

void ACPP_Character::CancelMoveFaster()
{

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	CurrentMaxSpeed = MovementSpeed;
}

void ACPP_Character::Dash()
{

	if (bCanDash) {

		bCanDash = false;

		GetCharacterMovement()->MaxWalkSpeed = DashSpeed;

		FTimerHandle AttackTimer;

		GetWorldTimerManager().SetTimer(AttackTimer, this, &ACPP_Character::CancelDash, DashTimeSec);

	}
}

void ACPP_Character::CancelDash()
{

	GetCharacterMovement()->MaxWalkSpeed = CurrentMaxSpeed;

}

void ACPP_Character::Jump()
{

	ACharacter::Jump();

}

void ACPP_Character::StopJumping()
{
	
	ACharacter::StopJumping();

}

void ACPP_Character::PunchLeft()
{

	if (PunchLeftMontage) {

		PlayAnimMontage(PunchLeftMontage);

	}

}

void ACPP_Character::PunchRight()
{

	if (PunchRightMontage) {

		PlayAnimMontage(PunchRightMontage);

	}

}

void ACPP_Character::KickLeft()
{

	if (KickLeftMontage) {

		bCanMove = false;
		PlayAnimMontage(KickLeftMontage);

	}

}

void ACPP_Character::KickRight()
{

	if (KickRightMontage) {

		bCanMove = false;
		PlayAnimMontage(KickRightMontage);

	}

}

void ACPP_Character::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	if (!bInterrupted)
		bCanMove = true;

}
