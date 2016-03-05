// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TOECharacter.h"
#include "TOEEnemyCharacter.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	FLYING_SKULL,
	SKELETON,
	MTUMBO
};


UCLASS()
class THE_TIME_OF_ENDING_API ATOEEnemyCharacter : public ATOECharacter
{
	GENERATED_BODY()	

public:


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void BasicAttack();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool isVulnerable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAbilityType vulnerableElement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maxWalkSpeed;

	UFUNCTION(BlueprintCallable, Category = "Debuff")
		virtual void OnSlow(float slowAmount_);
	UFUNCTION(BlueprintCallable, Category = "Debuff")
		virtual void OnSlowWithFalloff(float slowAmount_, float newSlowFalloffRate_);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		EEnemyType enemyName;



private:
	
		float slowFallOffRate;

	UFUNCTION(BlueprintCallable, Category = "Debuff")
		bool SlowStatus();

	UFUNCTION(BluePrintCallable, Category = "Debuff")
		void SlowFalloff(float DeltaSeconds_);
	
};
