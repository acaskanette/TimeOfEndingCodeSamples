// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activatable.h"
#include "WaterTower.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API AWaterTower : public AActivatable
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "RisingPlatform")
	virtual void onUse() override;
	
	virtual void ActivateProp_Implementation() override;
	
	
};
