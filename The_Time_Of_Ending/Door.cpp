// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Door.h"

void ADoor::BeginPlay()
{
	active = false;

	Super::BeginPlay();

}

void ADoor::onUse(){
	active = !active;
}

void ADoor::ActivateProp_Implementation()
{
	return Super::ActivateProp_Implementation();
}



