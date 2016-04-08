// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "RisingPlatform.h"

void ARisingPlatform::BeginPlay()
{
	active = false;

	Super::BeginPlay();

}

void ARisingPlatform::onUse(){
	active = !active;
}

void ARisingPlatform::ActivateProp_Implementation()
{
	return Super::ActivateProp_Implementation();
}

