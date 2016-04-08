// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "StateMachine.h"


// Sets default values for this component's properties
UStateMachine::UStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();

	if (currentState != nullptr)
		currentState->GetDefaultObject<AState>()->OnEnterState();
	
}


// Called every frame
void UStateMachine::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (currentState != nullptr)
		currentState->GetDefaultObject<AState>()->StateUpdate();
}

void UStateMachine::SwitchToState(FString name)
{
	for (int i = 0; i < states.Max(); i++)
	{
		AState* stateTemp = states[i].GetDefaultObject();
		
		if (stateTemp->stateName == name)
		{
			if (currentState != nullptr)
				currentState->GetDefaultObject<AState>()->OnExitState();

			currentState = states[i];

			stateTemp->OnEnterState();

			stateTemp = nullptr;
			break;
		}

		stateTemp = nullptr;
	}
}

void UStateMachine::AddState(TSubclassOf<AState> state)
{
	states.Add(state);
}