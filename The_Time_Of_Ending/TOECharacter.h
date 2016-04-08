// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "TOECharacter.generated.h"

UCLASS()
class THE_TIME_OF_ENDING_API ATOECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATOECharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Health Properties
	UPROPERTY(BlueprintReadOnly, Category = "Health")
		float maxHealth;

	UPROPERTY(BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", UIMin = "0.0"))
		float currentHealth;

	UPROPERTY(BlueprintReadWrite, Category = "Health")
		float currentTempHealth;

	UPROPERTY(BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float tempHealthTimeRemaining;


	// Health Methods
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetMaxHealth(float p_health);

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(float p_health);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void AddHealth(float delta);

	UFUNCTION(BluePrintCallable, Category = "Health")
		virtual void OnOutOfHealth();

	UFUNCTION(BluePrintCallable, Category = "Health")
		void AddTempHealth(float delta, float duration);

	UFUNCTION(BluePrintCallable, Category = "Health")
		void ResetTempHealth();


	// Mana Properties
	UPROPERTY(BlueprintReadOnly, Category = "Mana")
		float maxMana;

	UPROPERTY(BlueprintReadWrite, Category = "Mana")
		float currentMana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mana")
		float manaRegenerationRate;

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
		float timeSinceLastCast;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Charge")
		float currentCharge;


	// Mana Methods
	UFUNCTION(BlueprintCallable, Category = "Mana")
		void SetMaxMana(float p_mana);

	UFUNCTION(BlueprintCallable, Category = "Mana")
		float GetMaxMana();

	UFUNCTION(BlueprintCallable, Category = "Mana")
		float GetCurrentMana();

	UFUNCTION(BlueprintCallable, Category = "Mana")
		void SetCurrentMana(float p_mana);

	UFUNCTION(BlueprintCallable, Category = "Mana")
		bool AtMaxMana();

	UFUNCTION(BlueprintCallable, Category = "Mana")
		void AddMana(float delta);


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float jumpForce;

	virtual void StartHealthRegeneration();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void OnAbilityOverlap(AAbility *ability);

protected:

	virtual void MoveRight(float value);

	virtual void MoveForward(float value);

	AAbilityManager* abilityManager;

};
