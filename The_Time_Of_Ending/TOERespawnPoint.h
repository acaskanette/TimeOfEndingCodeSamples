// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Prop.h"
#include "TOERespawnPoint.generated.h"

class ATOERespawner;

UCLASS()
class THE_TIME_OF_ENDING_API ATOERespawnPoint : public AProp
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	ATOERespawnPoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 WaypointNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATOERespawner* RespawnManager;

	UFUNCTION(BlueprintCallable, Category = "Respawn")
		void NotifyRespawnManager();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Respawn")
		void DeactivateSpawn();

	void DeactivateSpawn_Implementation() {}

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* ReySpawnPoint;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* MhambiSpawnPoint;
};
