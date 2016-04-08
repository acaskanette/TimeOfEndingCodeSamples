// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TOEObject.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "Prop.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API AProp : public ATOEObject
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void onUse();	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
		bool canPlayerUse;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void OnAbilityOverlap(AAbility *ability);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		UStaticMeshComponent* GetStaticMesh();

	
};
