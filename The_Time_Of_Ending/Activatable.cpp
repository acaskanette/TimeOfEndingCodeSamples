// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Activatable.h"

bool AActivatable::getActive(){
	return active;
}

void AActivatable::BeginPlay()
{
	active = false;
	Super::BeginPlay();
}

void AActivatable::onUse(){
	active = !active;
}

void AActivatable::ActivateProp_Implementation()
{

}
