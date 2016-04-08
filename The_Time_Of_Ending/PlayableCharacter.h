// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TOECharacter.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "MainCamera.h"
#include "PlayableCharacterAnimInstance.h"
#include "PlayableCharacter.generated.h"


UENUM(BlueprintType)
enum class ECharacterName : uint8
{
	Mhambi,
	Rey
};

UENUM(BlueprintType)
enum class EAbilityLocation : uint8
{
	L2,
	R2
};
/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API APlayableCharacter : public ATOECharacter
{
	GENERATED_BODY()

	APlayableCharacter();

	UCameraComponent* mainCamera;

	const float ABILITY_COOLDOWN = 0.4f;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Jump() override;

	virtual void RollPressed();

	virtual void MoveRight(float value) override;

	virtual void MoveForward(float value) override;

	float lookH;
	float lookV;

	virtual void SetLookH(float v);

	virtual void SetLookV(float v);

	virtual void UpdateLookDirection();

	int R2AbilityIndex;

	int L2AbilityIndex;

	int highestUnlockedAbilityIndex;

	TMap<int, EAbilityType> abilities;

	virtual void CastL2Ability();

	virtual void CastR2Ability();

	virtual void SwapR2Ability();

	virtual void SwapL2Ability();

	virtual void FlipCamera();

	virtual void StartPressed();

	virtual void SelectPressed();

	virtual void MeleePressed();

	virtual void MeleeReleased();

	virtual void UsePressed();

	void HandleAttackAnimation(EAbilityType type);

	float currentChargeL2;
	float currentChargeR2;
	float maxCharge;
	bool chargeL2;
	bool chargeR2;
	float lastCharge;

	

	UFUNCTION()
		void StartChargingAbilityPowerL2();

	UFUNCTION()
		void StartChargingAbilityPowerR2();

	UFUNCTION(BluePrintCallable, Category = "Health")
		virtual void OnOutOfHealth() override;

	UPlayableCharacterAnimInstance *animInstance;

	FRotator lastRotation;

public:

	UFUNCTION(BlueprintCallable, Category = "Utility")
	AMainCamera* GetMainCamera();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Name")
	ECharacterName characterName;

	UFUNCTION(BlueprintCallable, Category = "Charge")
		float GetLastCharge();
};
