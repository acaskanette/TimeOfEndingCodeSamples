// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOERespawnPoint.h"
#include "TOERespawner.h"


// Sets default values
ATOERespawnPoint::ATOERespawnPoint() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaypointNumber = 0;
	IsActive = false;
	RespawnManager = nullptr;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MhambiSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("MhambiSpawnPoint"));
	MhambiSpawnPoint->SetRelativeLocation(FVector(200, -400, 0));
	MhambiSpawnPoint->AttachParent = RootComponent;
	ReySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ReySpawnPoint"));
	ReySpawnPoint->SetRelativeLocation(FVector(-200, -400, 0));
	ReySpawnPoint->AttachParent = RootComponent;
}

// Called when the game starts or when spawned
void ATOERespawnPoint::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATOERespawnPoint::Tick( float DeltaTime ) {
	Super::Tick(DeltaTime);
}

void ATOERespawnPoint::NotifyRespawnManager() {
	RespawnManager->SetRespawnPoint(this);
}