// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOEEnemyCharacter.h"




void ATOEEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Set default max walk speed
	maxWalkSpeed = this->GetCharacterMovement()->MaxWalkSpeed;
	slowFallOffRate = 10.0f;

}


void ATOEEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Check to see if slowed
	if (SlowStatus()) {
		SlowFalloff(DeltaSeconds);
	}

}


void ATOEEnemyCharacter::BasicAttack()
{
	abilityManager->CastAbility(EAbilityType::MELEE, 0.0, this);
}


// Slow Amount between 0 and 1, expressed as percentage slow
void ATOEEnemyCharacter::OnSlow(float slowAmount_) {
	
	this->GetCharacterMovement()->MaxWalkSpeed = slowAmount_ * maxWalkSpeed;

}

// Slow Amount between 0 and 1, expressed as percentage slow ; newSlowFalloffRate_ determines how fast you recover speed per second
void ATOEEnemyCharacter::OnSlowWithFalloff(float slowAmount_, float newSlowFalloffRate_) {

	this->GetCharacterMovement()->MaxWalkSpeed = slowAmount_ * maxWalkSpeed;
	slowFallOffRate = newSlowFalloffRate_;

}


// Returns true if I am slower than my max speed
bool ATOEEnemyCharacter::SlowStatus(){
	
	return (this->GetCharacterMovement()->MaxWalkSpeed < maxWalkSpeed);

}

// Increases speed by the slowFallOffRate each second until you reach max speed
void ATOEEnemyCharacter::SlowFalloff(float DeltaSeconds_) {
		
	this->GetCharacterMovement()->MaxWalkSpeed += DeltaSeconds_ * slowFallOffRate;

	if (this->GetCharacterMovement()->MaxWalkSpeed > maxWalkSpeed) {
		this->GetCharacterMovement()->MaxWalkSpeed = maxWalkSpeed;
	}

}