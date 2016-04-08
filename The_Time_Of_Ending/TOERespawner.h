// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TOERespawner.generated.h"

class ATOERespawnPoint;

UCLASS()
class THE_TIME_OF_ENDING_API ATOERespawner : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATOERespawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Respawn")
		void SetRespawnPoint(ATOERespawnPoint* newWaypoint);

	UFUNCTION(BlueprintCallable, Category = "Respawn")
		void RespawnPlayers();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Respawn")
		ATOERespawnPoint* LastWaypoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Respawn")
		float RespawnTime;
	
	void Respawn();
protected:
	FTimerHandle respawnTimer;
	bool respawning;
};