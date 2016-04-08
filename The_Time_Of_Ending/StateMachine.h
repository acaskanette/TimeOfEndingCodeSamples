// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "State.h"
#include "StateMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THE_TIME_OF_ENDING_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateMachine();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<AState> currentState;

	UPROPERTY(EditAnywhere, Category = "States")
	TArray<TSubclassOf<AState>> states;
	
	UFUNCTION(BlueprintCallable, Category = "StateFunction")
	void SwitchToState(FString name);

	UFUNCTION(BlueprintCallable,  Category = "StateFunction")
	void AddState(TSubclassOf<AState> state);
};
