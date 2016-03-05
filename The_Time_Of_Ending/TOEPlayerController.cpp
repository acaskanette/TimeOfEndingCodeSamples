//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "The_Time_Of_Ending.h"
#include "TOEPlayerController.h"
#include "MainCamera.h"
#include "TOELevelScriptActor.h"

ATOEPlayerController::ATOEPlayerController()
{
	MhambiPawn = NULL;
	ReyPawn = NULL;
}


UClass* ATOEPlayerController::GetPlayerPawnClass() 
{ 
	return MyPawnClass; 
}

void ATOEPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATOEPlayerController::DeterminePawnClass_Implementation()
{
	//if (IsLocalController()) //Only Do This Locally (NOT Client-Only, since Server wants this too!)
	//{
	//	/* Load Text File Into String Array */
	//	TArray<FString> TextStrings;
	//	const FString FilePath = FPaths::GameDir() + "Textfiles/PlayerSettings.txt";

	//	/* Use PawnA if the Text File tells us to */
	//	if (TextStrings[0] == "PawnA")
	//	{
	//		ServerSetPawn(PawnToUseA);
	//		return;
	//	}

	//	/* Otherwise, Use PawnB :) */
	//	ServerSetPawn(PawnToUseB);
	//	return;
	//}

	
}

bool ATOEPlayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass)
{
	return true;
}

void ATOEPlayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
{
	MyPawnClass = InPawnClass;

	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}