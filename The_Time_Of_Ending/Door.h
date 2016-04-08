// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activatable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ADoor : public AActivatable
{
	GENERATED_BODY()
private:

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Door")
		virtual void onUse() override;

	virtual void ActivateProp_Implementation() override;
	
	
};
