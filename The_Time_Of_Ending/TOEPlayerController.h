// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayableCharacter.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "PlayableCharacterAnimInstance.h"
#include "GameFramework/PlayerController.h"
#include "TOEPlayerController.generated.h"


///**
// * 
// */
UCLASS()
class THE_TIME_OF_ENDING_API ATOEPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	ATOEPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	UClass* GetPlayerPawnClass();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	virtual void DeterminePawnClass_Implementation();

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

	UPROPERTY()
	TSubclassOf<APawn> MyPawnClass;

	/* First Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APlayableCharacter> MhambiPawn;

	/* Second Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APlayableCharacter> ReyPawn;

};
