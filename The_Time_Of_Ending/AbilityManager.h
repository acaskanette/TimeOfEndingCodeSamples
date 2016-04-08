// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ability.h"
#include "AbilityManager.generated.h"

UCLASS()
class THE_TIME_OF_ENDING_API AAbilityManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAbilityManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool CastAbility(EAbilityType type, float energy, AActor* caster);

	
	TMap<FString, UClass*> abilities;
};
