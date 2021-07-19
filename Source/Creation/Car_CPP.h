// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Components/PrimitiveComponent.h"

#include "Car_CPP.generated.h"

/**
 * 
 */
UCLASS()
class CREATION_API ACar_CPP : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	ACar_CPP();

	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	//Movement Car Declaration Functions (Throttle, Steering, HandBrake, Supercharge, Hyperbrake)
	UFUNCTION(BlueprintCallable)
	float Throttle(float value);

	UFUNCTION(BlueprintCallable)
	float Steering(float value);

	UFUNCTION(BlueprintCallable)
	void HandBrakeON();
	UFUNCTION(BlueprintCallable)
	void HandBrakeOFF();

	UFUNCTION(BlueprintCallable)
	void UpdateAirControl(float DeltaTime);

	/* UFUNCTION(BlueprintCallable)
	void superChargeCarON();

	UFUNCTION(BlueprintCallable)
	void hyperBrake(); */


	//Camera and Mouse Input Function (Pitch and Yaw)
	UFUNCTION(BlueprintCallable)
	void CameraPitch(float axisValue);

	UFUNCTION(BlueprintCallable)
	void CameraYaw(float axisValue);

	void perspectiveToggle();


	//Variables for the car (Speed, Throttle Speed, Steering Speed)
	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float throttleSpeed;

	UPROPERTY(EditAnywhere)
	float steeringSpeed;

protected:
	//Camera Components 
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

};
