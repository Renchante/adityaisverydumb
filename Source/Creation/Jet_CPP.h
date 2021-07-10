// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Jet_CPP.generated.h"

UCLASS()
class CREATION_API AJet_CPP : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJet_CPP();


	//Camera Declaration Functions (Pitch and Yaw)
	UFUNCTION(BlueprintCallable)
	void cameraPitch(float value);

	UFUNCTION(BlueprintCallable)
	void cameraYaw(float value);


	//Jet Movement Declaration Functions (Throttle, Pitch, Roll, Yaw)
	UFUNCTION(BlueprintCallable)
	void jetThrottle(float value);

	UFUNCTION(BlueprintCallable)
	void jetPitch(float value);

	UFUNCTION(BlueprintCallable)
	void jetRoll(float value);

	UFUNCTION(BlueprintCallable)
	void jetYaw(float value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components for the Jet (Skeletal Mesh, Camera, Spring Arm)
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* JetMesh;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
