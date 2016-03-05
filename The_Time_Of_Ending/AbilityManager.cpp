// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Engine.h"
#include "PlayableCharacter.h"
#include "TOEEnemyCharacter.h"
#include "AbilityManager.h"


// Sets default values
AAbilityManager::AAbilityManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	/// Below sets up the Ability Map, mapping the name to the a Blueprint Ability to be spawned.

	// UNIVERSAL ABILITIES

	// Melee - All Characters
	ConstructorHelpers::FObjectFinder<UBlueprint> melee(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/Melee"));
	if (melee.Succeeded()){
		abilities.Add(FString("Melee"), melee.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// MHAMBI ABILITIES

	// Tidal Uppercut - Mhambi Water
	ConstructorHelpers::FObjectFinder<UBlueprint> tidalUppercut(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/TidalUppercut"));
	if (tidalUppercut.Succeeded()){
		abilities.Add(FString("Mhambi Water"), tidalUppercut.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Quake Strike - Mhambi Earth
	ConstructorHelpers::FObjectFinder<UBlueprint> quakeStrike(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/Quakestrike"));
	if (quakeStrike.Succeeded()){
		abilities.Add(FString("Mhambi Earth"), quakeStrike.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Tornado Thrust - Mhambi Wind
	ConstructorHelpers::FObjectFinder<UBlueprint> tornadoThrust(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/TornadoThrust"));
	if (tornadoThrust.Succeeded()){
		abilities.Add(FString("Mhambi Wind"), tornadoThrust.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// REY ABILITIES

	// Winds of Calm - Rey Wind
	ConstructorHelpers::FObjectFinder<UBlueprint> windsOfCalm(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/WindsOfCalm"));
	if (windsOfCalm.Succeeded()){
		abilities.Add(FString("Rey Wind"), windsOfCalm.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Healing Rain - Rey Water
	ConstructorHelpers::FObjectFinder<UBlueprint> healingRain(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/HealingRain"));
	if (healingRain.Succeeded()){
		abilities.Add(FString("Rey Water"), healingRain.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Mud Ball - Rey Earth
	ConstructorHelpers::FObjectFinder<UBlueprint> mudBall(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/MudBall"));
	if (mudBall.Succeeded()){
		abilities.Add(FString("Rey Earth"), mudBall.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));



	// FLYING SKULL ABILITIES
	
	// Flame Shot - FlyingSkull Fire
	ConstructorHelpers::FObjectFinder<UBlueprint> flameShot(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/FlameShot"));
	if (flameShot.Succeeded()){
		abilities.Add(FString("FlyingSkull Fire"), flameShot.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// MTUMBO ABILITIES

	// Flame Shot - Mtumbo Fire
	ConstructorHelpers::FObjectFinder<UBlueprint> flameShotM(TEXT("/Game/TimeOfEndingAssets/Blueprints/Abilities/FlameShot"));
	if (flameShotM.Succeeded()){
		abilities.Add(FString("Mtumbo Fire"), flameShotM.Object->GeneratedClass);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));
	


}

// Called when the game starts or when spawned
void AAbilityManager::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AAbilityManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AAbilityManager::CastAbility(EAbilityType type, float energy, AActor* caster)
{
	bool castSuccess = true;

	FActorSpawnParameters spawnParamaters;
	spawnParamaters.Owner = caster;
	spawnParamaters.Instigator = Cast<APawn>(caster);
	

	FString characterName = "Rey"; // Default Caster
	FString elementName = "Melee"; // Default Ability

	APlayableCharacter* character = Cast<APlayableCharacter>(caster);

	if (character)
	{

		// What character is spawning it
		if (character->characterName == ECharacterName::Mhambi)
			characterName = "Mhambi";
		else
			characterName = "Rey";

		// What type do I spawn
		switch (type)
		{
		case EAbilityType::MELEE:
			characterName = "";
			break;
		case EAbilityType::WATER:
			elementName = " Water";
			break;
		case EAbilityType::EARTH:
			elementName = " Earth";
			break;
		case EAbilityType::WIND:
			elementName = " Wind";
			break;
		}

		//Spawn Ability from Ability Map
		if (abilities.Contains(characterName + elementName))
		{
			GetWorld()->SpawnActor<AAbility>(abilities[characterName + elementName], caster->GetActorLocation(), caster->GetActorRotation(), spawnParamaters);
		}
		else
			UE_LOG(YourLog, Warning, TEXT("Ability not found in Ability Map"));
		
		return castSuccess;


	}

	// If it's not a Character, cast to Enemy
	else {

		ATOEEnemyCharacter* enemy = Cast<ATOEEnemyCharacter>(caster);

		if (enemy)
		{

			// What enemy type is casting
			switch (enemy->enemyName) {
			case EEnemyType::FLYING_SKULL:
				characterName = "FlyingSkull";
				break;
			case EEnemyType::SKELETON:
				characterName = "Skeleton";
				break;
			case EEnemyType::MTUMBO:
				characterName = "Mtumbo";
				break;

			}

			// What element is the enemy casting
			switch (type)
			{
			case EAbilityType::MELEE:
				characterName = "";
				break;
			case EAbilityType::FIRE:
				elementName = " Fire";
				break;
			case EAbilityType::SPECIAL:
				elementName = " Special";
				break;

			}

			//Spawn Ability from Ability Map
			if (abilities.Contains(characterName + elementName))
			{
				GetWorld()->SpawnActor<AAbility>(abilities[characterName + elementName], caster->GetActorLocation(), caster->GetActorRotation(), spawnParamaters);
			}
			else
				UE_LOG(YourLog, Warning, TEXT("Ability not found in Ability Map"));

		}
		else
			return false;


		return false;
	}
}
