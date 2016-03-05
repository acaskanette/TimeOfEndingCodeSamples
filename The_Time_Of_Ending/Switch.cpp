// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Switch.h"

void ASwitch::BeginPlay()
{
	active = false;
	Super::BeginPlay();

}

void ASwitch::onUse(){
	active = !active;
}

void ASwitch::setIsNear(bool b){
	isNear = b;
}

bool ASwitch::getIsNear(){
	return isNear;
}

