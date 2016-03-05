// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activator.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API APressurePlate : public AActivator
{
	GENERATED_BODY()
private:

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "PressurePlate")
		virtual void onUse() override;

	UFUNCTION(BlueprintCallable, Category = "PressurePlate")
		virtual void onLeave();	
	
};
