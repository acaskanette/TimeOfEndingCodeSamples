// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "MainCamera.h"
#include "TOECharacter.h"


// Sets default values
ATOECharacter::ATOECharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATOECharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Iterate through all actor to see if there is already a AbilityManager object in the scene. */
	for (TActorIterator<AAbilityManager> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		if (*actorItr != NULL){
			abilityManager = *actorItr;
			break;
		}
	}
	if (abilityManager == NULL)
		abilityManager = Cast<AAbilityManager>(GetWorld()->SpawnActor(AAbilityManager::StaticClass()));

	SetMaxHealth(100.0f);
	SetCurrentHealth(100.0f);
}

// Called every frame
void ATOECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(timeSinceLastCast));
	if (timeSinceLastCast >= 2.0f) {
		AddMana(manaRegenerationRate);
	}
	else
		timeSinceLastCast += DeltaTime;

	// Managing Temporary Health
	if (tempHealthTimeRemaining >= 0.0f) {
		tempHealthTimeRemaining -= DeltaTime;
		if (tempHealthTimeRemaining < 0.0f) {
			ResetTempHealth();
		}
	}
}

// Called to bind functionality to input
void ATOECharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATOECharacter::SetMaxHealth(float p_Health)
{
	maxHealth = p_Health;
}

void ATOECharacter::SetCurrentHealth(float p_Health)
{
	currentHealth = p_Health;
	float max = GetMaxHealth();

	if (currentHealth > max)
		currentHealth = max;
	else if (currentHealth <= 0.0f)
		OnOutOfHealth();

}

float ATOECharacter::GetMaxHealth()
{
	return maxHealth;
}

float ATOECharacter::GetCurrentHealth()
{
	return currentHealth;
}


void ATOECharacter::AddHealth(float delta) {
	SetCurrentHealth(GetCurrentHealth() + delta);
}

void ATOECharacter::OnOutOfHealth() {
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString("Player Died"));
}


// Adds temporary Health pool for the duration
void ATOECharacter::AddTempHealth(float delta, float duration) {

	currentTempHealth += delta;
	tempHealthTimeRemaining = duration;

}

// Resets Temporary Health Pool to 0
void ATOECharacter::ResetTempHealth() {

	currentTempHealth = 0;

}



void ATOECharacter::SetMaxMana(float p_Mana) {
	maxMana = p_Mana;
}

void ATOECharacter::SetCurrentMana(float p_Mana) {
	currentMana = p_Mana;
	float max = GetMaxMana();

	if (currentMana > max)
		currentMana = max;
	else if (currentMana < 0.0f)
		currentMana = 0.0f;

}

float ATOECharacter::GetMaxMana() {
	return maxMana;
}

float ATOECharacter::GetCurrentMana() {
	return currentMana;
}

bool ATOECharacter::AtMaxMana() {
	return (currentMana >= maxMana);
}

void ATOECharacter::AddMana(float delta) {
	SetCurrentMana(GetCurrentMana() + delta);
}


void ATOECharacter::MoveRight(float value)
{

}

void ATOECharacter::MoveForward(float value)
{

}

void ATOECharacter::StartHealthRegeneration()
{

}

void ATOECharacter::OnAbilityOverlap_Implementation(AAbility *ability)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString("Taking The ability info"));
}