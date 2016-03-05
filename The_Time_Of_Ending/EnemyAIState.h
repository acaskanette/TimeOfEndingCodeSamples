// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TOEEnemyCharacter.h"
/**
 * 
 */
class THE_TIME_OF_ENDING_API EnemyAIState
{
public:
	EnemyAIState();
	~EnemyAIState();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATOEEnemyCharacter *owningCharacter;

	UFUNCTION(BlueprintCallable, Category = "Transition")
		virtual void OnCreate(ATOEEnemyCharacter *owningCharacter_);
	UFUNCTION(BlueprintCallable, Category = "Transition")
		virtual void OnEnter();
	UFUNCTION(BlueprintCallable, Category = "Transition")
		virtual void OnExit();
	UFUNCTION(BlueprintCallable, Category = "Transition")
		virtual void OnStay();
	UFUNCTION(BlueprintCallable, Category = "Transition")
		virtual void OnDestroy();

};
