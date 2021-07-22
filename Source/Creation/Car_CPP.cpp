// Fill out your copyright notice in the Description page of Project Settings.


#include "Car_CPP.h"

ACar_CPP::ACar_CPP()
{
	UWheeledVehicleMovementComponent4W* vehicleMovement = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());

	//Tire Load
	vehicleMovement->MinNormalizedTireLoad = 0.0f;
	vehicleMovement->MinNormalizedTireLoadFiltered = 0.2f;
	vehicleMovement->MaxNormalizedTireLoad = 2.0f;
	vehicleMovement->MaxNormalizedTireLoadFiltered = 2.0f;

	//Torque Setup
	vehicleMovement->MaxEngineRPM = 5700.0f;
	vehicleMovement->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	vehicleMovement->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 400.0f);
	vehicleMovement->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1890.0f, 500.0f);
	vehicleMovement->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(5730.0f, 400.0f);

	//Steering Setup
	vehicleMovement->SteeringCurve.GetRichCurve()->Reset();
	vehicleMovement->SteeringCurve.GetRichCurve()->AddKey(0.0f, 1.0f);
	vehicleMovement->SteeringCurve.GetRichCurve()->AddKey(40.0f, 0.7f);
	vehicleMovement->SteeringCurve.GetRichCurve()->AddKey(120.0f, 0.6f); 

	vehicleMovement->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	vehicleMovement->DifferentialSetup.FrontRearSplit = 0.65f;

	//Gear Box Setup (Automatic)
	vehicleMovement->TransmissionSetup.bUseGearAutoBox = true;
	vehicleMovement->TransmissionSetup.GearSwitchTime = 0.15f;
	vehicleMovement->TransmissionSetup.GearAutoBoxLatency = 1.0f;


	//Setting up Variables (Speed)
	Speed = 4000.0f;
	throttleSpeed = 10.0f;
	steeringSpeed = 1.0f;
	radioON = false;

	//Setting up the spring arm and camera components 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

/* void ACar_CPP::Tick(float DeltaTime)
{

	UpdateAirControl(DeltaTime);
} */

void ACar_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Inputs Car Movements (Moveing forward and turning)
	PlayerInputComponent->BindAxis("MoveForward", this, &ACar_CPP::Throttle);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACar_CPP::Steering);

	//Axis Inputs Camera (Pitch and Yaw Camera)
	PlayerInputComponent->BindAxis("LookUp", this, &ACar_CPP::CameraPitch);
	PlayerInputComponent->BindAxis("Turn", this, &ACar_CPP::CameraYaw);



	//Action Inputs (Handbrake on and off)
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ACar_CPP::HandBrakeON);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ACar_CPP::HandBrakeOFF);

	//Action Inputs (Changing Perspective from Third Person to First Person)
	PlayerInputComponent->BindAction("Change Perspective", IE_Pressed, this, &ACar_CPP::perspectiveToggle);
}


//Car Movement Definition Functions (Throttle and Steering)
void ACar_CPP::Throttle(float value)
{
	value *= throttleSpeed;
	GetVehicleMovementComponent()->SetThrottleInput(value);
}

void ACar_CPP::Steering(float value)
{
	value *= steeringSpeed;
	GetVehicleMovementComponent()->SetSteeringInput(value);
}


//Handbrake Definition Functions
void ACar_CPP::HandBrakeON()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void ACar_CPP::HandBrakeOFF()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ACar_CPP::UpdateAirControl(float DeltaTime)
{

}

/* //Supercharge Definition Functions (On and Off)
void ACar_CPP::superChargeCarON()
{
	float zVelocity = GetMesh()->GetPhysicsLinearVelocity().Z;
	if (zVelocity < 10.0f && zVelocity > -10.0f)
	{
		FVector newVelocity = GetActorForwardVector() * Speed;
		GetMesh()->SetPhysicsLinearVelocity(newVelocity, true);
	}
}

//Hyperbrake Definition Function
void ACar_CPP::hyperBrake()
{
	float zVelocity = GetMesh()->GetPhysicsLinearVelocity().Z;
	if (zVelocity < 10.0f && zVelocity > -10.0f)
	{
		FVector newVelocity = GetVelocity() * -1.0f;
		GetMesh()->SetPhysicsLinearVelocity(newVelocity, true);
	}
} */

//Camera Definition Functions (Pitch and Yaw)
void ACar_CPP::CameraPitch(float axisValue)
{
	if (axisValue != 0.0f)
	{
		AddControllerPitchInput(axisValue);
	}
}

void ACar_CPP::CameraYaw(float axisValue)
{
	if (axisValue != 0.0f)
	{
		AddControllerYawInput(axisValue);
	}
}

void ACar_CPP::perspectiveToggle()
{
	float targetArm = SpringArm->TargetArmLength;
	if (targetArm == 500.0f)
	{
		SpringArm->TargetArmLength = 0.0f;
		SpringArm->bEnableCameraLag = false;
	}
	else
	{
		SpringArm->TargetArmLength = 500.0f;
		SpringArm->bEnableCameraLag = true;
	}
}

bool ACar_CPP::radioToggle()
{
	if (radioON == false) 
	{
		radioON = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Playing Radio GaGa!"));
	}
	else
	{
		radioON = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("STOPPED Radio!"));
	}

	return radioON;
}
