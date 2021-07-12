// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet_CPP.h"

// Sets default values
AJet_CPP::AJet_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Define Jet Movement Variables (Throttle, Max Throttle)
	throttleValue = 0.0f;
	maxThrottleValue = 3000.0f;

	//Define all the Components for the Jet
	JetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet Mesh"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(JetMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	RootComponent = JetMesh;
}

// Called when the game starts or when spawned
void AJet_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJet_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newVelocity = GetActorForwardVector() * throttleValue;
	JetMesh->SetPhysicsLinearVelocity(newVelocity);
}

// Called to bind functionality to input
void AJet_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* AXIS INPUTS */
	//Camera Inputs (Pitch & Yaw)
	PlayerInputComponent->BindAxis("LookUp", this, &AJet_CPP::cameraPitch);
	PlayerInputComponent->BindAxis("Turn", this, &AJet_CPP::cameraYaw);

	//Jet Movement Inputs (Throttle, Pitch, Yaw, Roll)
	PlayerInputComponent->BindAxis("MoveForward", this, &AJet_CPP::jetPitch);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJet_CPP::jetYaw);
	PlayerInputComponent->BindAxis("Roll", this, &AJet_CPP::jetRoll);
	PlayerInputComponent->BindAxis("Throttle", this, &AJet_CPP::jetThrottle);

	/* ACTION INPUTS */
	//Jet Feature Inputs (Shootings)
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJet_CPP::shootBullets);
}

//Camera Definition Functions (Pitch & Yaw)
void AJet_CPP::cameraPitch(float value)
{
	if (value != 0.0f)
	{
		AddControllerPitchInput(value);
	}
}

void AJet_CPP::cameraYaw(float value)
{
	if (value != 0.0f)
	{
		AddControllerYawInput(value);
	}
}


//Jet Movement Declaration Functions (Throttle, Pitch, Roll, Yaw)
void AJet_CPP::jetThrottle(float value)
{
	float newThrottle = (value * 10.0f) + throttleValue;
	if (newThrottle <= maxThrottleValue && newThrottle >= 0.0f)
	{
		throttleValue = newThrottle;
	}
	else if (newThrottle > maxThrottleValue)
	{
		throttleValue = maxThrottleValue;
	}
	else
	{
		throttleValue = 0.0f;
	}
}

void AJet_CPP::jetPitch(float value)
{

}

void AJet_CPP::jetRoll(float value)
{

}

void AJet_CPP::jetYaw(float value)
{

}


//Jet Feature Definition Functions (Shooting)
void AJet_CPP::shootBullets()
{

}