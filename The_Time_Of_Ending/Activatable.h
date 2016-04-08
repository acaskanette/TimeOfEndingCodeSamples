// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Prop.h"
#include "Activator.h"
#include "Activatable.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API AActivatable : public AProp
{
	GENERATED_BODY()

private:

public:
	bool active;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Activatable")
		virtual bool getActive();

	UFUNCTION(BlueprintCallable, Category = "Activatable")
		virtual void onUse() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activatable")
		void ActivateProp();
	virtual void ActivateProp_Implementation();
	
};
