// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Prop.h"
//#include "Activatable.h"
#include "Activator.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API AActivator : public AProp
{
	GENERATED_BODY()

private:
	
public:
	bool active;

	UFUNCTION(BlueprintCallable, Category = "Activator")
		virtual bool getActive();

	
	
};
