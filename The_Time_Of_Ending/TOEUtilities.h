// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TOEUtilities.generated.h"

/**
 *
 */
UCLASS()
class THE_TIME_OF_ENDING_API UTOEUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "File IO")
		static bool LoadTextFileToString(const FString& fileName, FString& fileContents);

	UFUNCTION(BlueprintCallable, Category = "String")
		static TArray<FString> ParseStringByLines(const FString& string);
};
