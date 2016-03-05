// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "PlayableCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class THE_TIME_OF_ENDING_API UPlayableCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables")
	float velocityX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables")
	float velocityY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking Variables")
	bool isGroundSmash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking Variables")
	bool isMeleeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking Variables")
	bool isProjectileAttack;
};