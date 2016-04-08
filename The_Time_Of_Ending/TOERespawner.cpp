// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOERespawner.h"
#include "TOERespawnPoint.h"
#include "TOECharacter.h"

ATOERespawner::ATOERespawner() {
	LastWaypoint = nullptr;
	RespawnTime = 3.0F;

	respawning = false;
}

void ATOERespawner::BeginPlay() {
	Super::BeginPlay();
	TArray<AActor*> tempRespawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATOERespawnPoint::StaticClass(), tempRespawnPoints);

	for (AActor* actor : tempRespawnPoints) {
		ATOERespawnPoint* point = Cast<ATOERespawnPoint>(actor);
		if (point != nullptr) {
			if (point->WaypointNumber == 0)
				LastWaypoint = point;
		} else 
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("NOPE"));
	}
}

void ATOERespawner::SetRespawnPoint(ATOERespawnPoint* newWaypoint) {
	LastWaypoint = newWaypoint;
}

void ATOERespawner::RespawnPlayers() {
	if (!respawning) {
		GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ATOERespawner::Respawn, RespawnTime);
		respawning = true;
		// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Triggered respawn"));
	}
}

void ATOERespawner::Respawn() {
	APawn* Mhambi = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* Rey = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);

	if (LastWaypoint != nullptr && Mhambi != nullptr && Rey != nullptr) {
		Mhambi->SetActorLocation(LastWaypoint->MhambiSpawnPoint->GetComponentLocation() + FVector(0, 0, 100));
		Rey->SetActorLocation(LastWaypoint->ReySpawnPoint->GetComponentLocation() + FVector(0, 0, 100));
	}

	GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
	respawning = false;
	// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Respawned"));
}