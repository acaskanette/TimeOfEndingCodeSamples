// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "MainCamera.h"


// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	targetRotation = rotation1;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetVisibility(false);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = false; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	//CameraBoom->SetWorldRotation(rotation1);
	CameraBoom->bDoCollisionTest = 0;

	// Create a camera and attach to boom
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	minBoomLength = 1000;
	maxBoomLength = 1500;
	rotationSpeed = 400;

}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	playerController1 = GetWorld()->GetFirstPlayerController();
	playerController1->SetViewTarget(this);

	playerController2 = UGameplayStatics::GetPlayerController(this, 1);
	playerController2->SetViewTarget(this);
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// When 2 player

	if (playerController2->GetPawn()){

		FVector cameraPosition;
		FVector player1to2 = playerController1->GetPawn()->GetActorLocation() - playerController2->GetPawn()->GetActorLocation();

		cameraPosition = playerController2->GetPawn()->GetActorLocation() + player1to2 / 2;

		this->SetActorLocation(cameraPosition);

		CameraBoom->TargetArmLength = FMath::Clamp<float>(player1to2.Size(),minBoomLength,maxBoomLength);
	}

	/*FVector cameraPosition;
	cameraPosition = playerController1->GetPawn()->GetActorLocation();
	this->SetActorLocation(cameraPosition);*/

	if (GetActorRotation() != targetRotation)
		SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(),targetRotation,DeltaTime,rotationSpeed));
}

void AMainCamera::FlipCameraAngle()
{
	if (targetRotation == rotation1)
		targetRotation = rotation2;
	else
		targetRotation = rotation1;
}