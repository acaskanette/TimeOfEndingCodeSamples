// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TOEObject.generated.h"

UCLASS()
class THE_TIME_OF_ENDING_API ATOEObject : public AActor
{
	GENERATED_BODY()
	
public:	

	bool dynamic;

	// Sets default values for this actor's properties
	ATOEObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void onDestroy();
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void onOverlap(AActor other);
};