// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "PlayableCharacter.h"
#include "The_Time_Of_EndingGameMode.h"


AThe_Time_Of_EndingGameMode::AThe_Time_Of_EndingGameMode()
{
	// set default pawn class to our Blueprinted character
	ConstructorHelpers::FObjectFinder<UClass> MhambiPawnBPClass(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Character/Mhambi.Mhambi_C'"));
	ConstructorHelpers::FObjectFinder<UClass> ReyPawnBPClass(TEXT("Class'/Game/TimeOfEndingAssets/Blueprints/Character/Rey.Rey_C'"));

	if (ReyPawnBPClass.Object != nullptr)
		ReyPawnClass = ReyPawnBPClass.Object;

	if (MhambiPawnBPClass.Object != nullptr)
		MhambiPawnClass = MhambiPawnBPClass.Object;

	DefaultPawnClass = MhambiPawnClass;
}

void AThe_Time_Of_EndingGameMode::BeginPlay() {
	Super::BeginPlay();

	DefaultPawnClass = MhambiPawnClass;

	APlayerController* player1 = UGameplayStatics::GetPlayerController(this, 0);

	DefaultPawnClass = ReyPawnClass;

	FString error;
	ULocalPlayer* player2 = GetGameInstance()->CreateLocalPlayer(1, error, true);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, error);
}