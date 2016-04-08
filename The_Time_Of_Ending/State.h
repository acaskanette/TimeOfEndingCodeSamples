// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Object.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, abstract, Config = Engine, Blueprintable)
class THE_TIME_OF_ENDING_API AState : public AActor
{
	GENERATED_UCLASS_BODY()

	//AState();

	//AState(const FObjectInitializer& object);

public:
	UFUNCTION(BlueprintNativeEvent, Category = "StateFunction")
	void OnEnterState();

	UPROPERTY(BlueprintReadWrite, Category = "StateProperty")
	bool finishedEntering;

	UFUNCTION(BlueprintNativeEvent, Category = "StateFunction")
	void StateUpdate();
	
	UFUNCTION(BlueprintNativeEvent, Category = "StateFunction")
	void OnExitState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateProperty")
	FString stateName;
};
