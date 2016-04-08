// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "MiniMap2D.h"
#include "PlayableCharacter.h"

AMiniMap2D::AMiniMap2D() {

	PrimaryActorTick.bCanEverTick = true;

}

void AMiniMap2D::BeginPlay() {

	Super::BeginPlay();

	// Rotate the camera boom to face the ground
	//if (GetCaptureComponent2D() != NULL)
	//	GetCaptureComponent2D()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	minimapRotation = 135.0f;			
	
}


void AMiniMap2D::SetCenter() {

	// Get reference to player for position purposes
	if (mainCamera != NULL) {
		float cameraX = mainCamera->GetTransform().GetLocation().X;
		float cameraY = mainCamera->GetTransform().GetLocation().Y;
		// Set Center of the minimap picture to the player's position
		SetActorLocation(FVector(cameraX, cameraY, SPAWN_HEIGHT));
		SetActorRotation(FRotator(-90.f, minimapRotation, 0.f));
	}
	else if (mainCamera == NULL || playerPawn == NULL && UGameplayStatics::GetRealTimeSeconds(GetWorld()) > 1.5f) {

		playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (playerPawn !=NULL)
			mainCamera = Cast<APlayableCharacter>(playerPawn)->GetMainCamera();
	}
	
	

}

void AMiniMap2D::RotateMiniMap() {

	minimapRotation += 180.0f;
	//minimapRotation = minimapRotation % 360.0f;

}

APawn* AMiniMap2D::GetPlayerPawn() {

	return playerPawn;

}

AMainCamera* AMiniMap2D::GetMainCamera() {

	return mainCamera;

}


void AMiniMap2D::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);
	
	// Update the center every frame
	SetCenter();
}

