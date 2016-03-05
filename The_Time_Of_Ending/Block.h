// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TOEObject.h"
#include "Block.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ABlock : public ATOEObject 
{
	GENERATED_BODY()

public:
	bool physics;

	virtual void BeginPlay() override;

	virtual void onStep();

	virtual void onUnstep();

	virtual void onMove();	
	
	
};
