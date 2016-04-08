// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "WaterTower.h"

void AWaterTower::BeginPlay()
{
	active = false;

	Super::BeginPlay();

}

void AWaterTower::onUse(){
	active = true;
}

void AWaterTower::ActivateProp_Implementation()
{
	return Super::ActivateProp_Implementation();
}
