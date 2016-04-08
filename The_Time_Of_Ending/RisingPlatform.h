// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activatable.h"
#include "RisingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ARisingPlatform : public AActivatable
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "RisingPlatform")
		virtual void onUse() override;
	
	virtual void ActivateProp_Implementation() override;
	
};
