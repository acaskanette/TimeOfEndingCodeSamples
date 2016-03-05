// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "PressurePlate.h"


void APressurePlate::BeginPlay()
{
	active = false;
	Super::BeginPlay();

}

void APressurePlate::onUse(){
	active = !active;
}

void APressurePlate::onLeave(){
	active = false;
}

