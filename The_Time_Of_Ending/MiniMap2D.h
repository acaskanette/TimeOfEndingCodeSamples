// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/SceneCapture2D.h"
#include "MainCamera.h"
#include "MiniMap2D.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API AMiniMap2D : public ASceneCapture2D
{
	GENERATED_BODY()
	
	
public:

	AMiniMap2D();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SetCenter")
	void SetCenter();

	UFUNCTION(BlueprintCallable, Category = "RotateMiniMap")
	void RotateMiniMap();

	UFUNCTION(BlueprintCallable, Category = "Properties")
		APawn* GetPlayerPawn();
	
	UFUNCTION(BlueprintCallable, Category = "Properties")
		AMainCamera* GetMainCamera();

private:

	APawn* playerPawn;
	AMainCamera* mainCamera;

	const float SPAWN_HEIGHT = 200000.f;
	float minimapRotation;


};
