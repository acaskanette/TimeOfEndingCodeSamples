// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayableCharacter.h"
#include "Engine/LevelScriptActor.h"
#include "TOELevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ATOELevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

	ATOELevelScriptActor();

public:
	UFUNCTION(BlueprintNativeEvent, Category = "HUD")
	void UpdateHUD(ECharacterName name, EAbilityLocation abilityLocation, EAbilityType currentlyEquipedType);

	UFUNCTION(BlueprintNativeEvent, Category = "HUD")
	void UpdateHealthAndMana(ECharacterName name, float currentHealth, float currentMana, float currentTempHealth, float currentCharge);

	UPROPERTY(BlueprintReadWrite, Category = "Player Spawns")
	AActor* player1Spawn;
	
	UPROPERTY(BlueprintReadWrite, Category = "Player Spawns")
	AActor* player2Spawn;
};
