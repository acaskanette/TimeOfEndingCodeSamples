// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activator.h"
#include "Switch.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ASwitch : public AActivator
{
	GENERATED_BODY()

private:
	bool isNear;

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Switch")
		virtual void onUse() override;
	
	UFUNCTION(BlueprintCallable, Category = "Switch")
		virtual bool getIsNear();
	UFUNCTION(BlueprintCallable, Category = "Switch")
		virtual void setIsNear(bool b);
};
