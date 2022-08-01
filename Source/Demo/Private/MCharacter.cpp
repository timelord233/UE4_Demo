// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AMCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AMCharacter::BeginCrouch()
{

}

void AMCharacter::EndCrouch()
{

}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AMCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMCharacter::AddControllerYawInput);
}

