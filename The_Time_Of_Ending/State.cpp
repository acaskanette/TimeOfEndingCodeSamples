// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "State.h"

AState::AState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

//AState::AState()
//{
//
//}

void AState::OnEnterState_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "State Enter");
}

void AState::StateUpdate_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "State Update");
}

void AState::OnExitState_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "State Exit");
}