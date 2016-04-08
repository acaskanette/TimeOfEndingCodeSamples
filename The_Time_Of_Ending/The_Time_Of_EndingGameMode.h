// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "The_Time_Of_EndingGameMode.generated.h"

/**
 *
 */
UCLASS()
class THE_TIME_OF_ENDING_API AThe_Time_Of_EndingGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AThe_Time_Of_EndingGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		UClass* MhambiPawnClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		UClass* ReyPawnClass;
};
