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
	ConstructorHelpers::FObjectFinder<UClass> melee(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/Melee.Melee_C'"));
	if (melee.Succeeded()){
		abilities.Add(FString("Melee"), melee.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// MHAMBI ABILITIES

	// Tidal Uppercut - Mhambi Water
	ConstructorHelpers::FObjectFinder<UClass> tidalUppercut(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/TidalUppercut.TidalUppercut_C'"));
	if (tidalUppercut.Succeeded()){
		abilities.Add(FString("Mhambi Water"), tidalUppercut.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Quake Strike - Mhambi Earth
	ConstructorHelpers::FObjectFinder<UClass> quakeStrike(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/Quakestrike.Quakestrike_C'"));
	if (quakeStrike.Succeeded()){
		abilities.Add(FString("Mhambi Earth"), quakeStrike.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Tornado Thrust - Mhambi Wind
	ConstructorHelpers::FObjectFinder<UClass> tornadoThrust(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/TornadoThrust.TornadoThrust_C'"));
	if (tornadoThrust.Succeeded()){
		abilities.Add(FString("Mhambi Wind"), tornadoThrust.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// REY ABILITIES

	// Winds of Calm - Rey Wind
	ConstructorHelpers::FObjectFinder<UClass> windsOfCalm(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/WindsOfCalm.WindsOfCalm_C'"));
	if (windsOfCalm.Succeeded()){
		abilities.Add(FString("Rey Wind"), windsOfCalm.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Healing Rain - Rey Water
	ConstructorHelpers::FObjectFinder<UClass> healingRain(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/HealingRain.HealingRain_C'"));
	if (healingRain.Succeeded()){
		abilities.Add(FString("Rey Water"), healingRain.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));

	// Mud Ball - Rey Earth
	ConstructorHelpers::FObjectFinder<UClass> mudBall(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/MudBall.MudBall_C'"));
	if (mudBall.Succeeded()){
		abilities.Add(FString("Rey Earth"), mudBall.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));



	// FLYING SKULL ABILITIES
	
	// Flame Shot - FlyingSkull Fire
	ConstructorHelpers::FObjectFinder<UClass> flameShot(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/MiniFlameShot.MiniFlameShot_C'"));
	if (flameShot.Succeeded()){
		abilities.Add(FString("FlyingSkull Fire"), flameShot.Object);
		UE_LOG(YourLog, Warning, TEXT("has Succeeded"));
	}
	else
		UE_LOG(YourLog, Warning, TEXT("Did not succeed"));


	// MTUMBO ABILITIES

	// Flame Shot - Mtumbo Fire
	ConstructorHelpers::FObjectFinder<UClass> flameShotM(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Abilities/FlameShot.FlameShot_C'"));
	if (flameShotM.Succeeded()){
		abilities.Add(FString("Mtumbo Fire"), flameShotM.Object);
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
