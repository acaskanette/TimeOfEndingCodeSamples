// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "PlayableCharacter.h"
#include "The_Time_Of_EndingGameMode.h"


AThe_Time_Of_EndingGameMode::AThe_Time_Of_EndingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TimeOfEndingAssets/Blueprints/Character/Mhambi"));
	static ConstructorHelpers::FClassFinder<APawn> ReyPawnBPClass(TEXT("/Game/TimeOfEndingAssets/Blueprints/Character/Rey"));

	ReyPawnClass = ReyPawnBPClass.Class;

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AThe_Time_Of_EndingGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* player1 = UGameplayStatics::GetPlayerController(this, 0);

	DefaultPawnClass = ReyPawnClass;

	FString error;

	ULocalPlayer* player2 = GetGameInstance()->CreateLocalPlayer(1, error, true);

}