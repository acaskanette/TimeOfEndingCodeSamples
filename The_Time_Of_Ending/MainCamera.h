// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MainCamera.generated.h"

UCLASS()
class THE_TIME_OF_ENDING_API AMainCamera : public AActor
{
	GENERATED_BODY()
	
	/** Main Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	USphereComponent* Sphere;

public:	
	// Sets default values for this actor's properties
	AMainCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION(BlueprintCallable, Category = "Utility")
	void FlipCameraAngle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Variables")
	float minBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Variables")
	float maxBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Variables")
	float rotationSpeed;

private:

	APlayerController* playerController1;
	APlayerController* playerController2;
	
	const FRotator rotation1 = FRotator(325.f, 135.f, 0.f);
	const FRotator rotation2 = FRotator(325.f, -45.f, 0.f);

	FRotator targetRotation;

};
