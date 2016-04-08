// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Prop.h"

void AProp::BeginPlay()
{
	Super::BeginPlay();

	canPlayerUse = false;

}

void AProp::onUse(){

}


void AProp::OnAbilityOverlap_Implementation(AAbility *ability)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString("Prop - OnAbilityOverlap"));
}


UStaticMeshComponent* AProp::GetStaticMesh_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString("Returning Static Mesh"));
	return nullptr;
}