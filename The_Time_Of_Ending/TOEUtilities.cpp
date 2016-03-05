// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOEUtilities.h"

bool UTOEUtilities::LoadTextFileToString(const FString& fileName, FString& fileContents) {
	return FFileHelper::LoadFileToString(fileContents, *(FPaths::GameDir() + fileName));
}

TArray<FString> UTOEUtilities::ParseStringByLines(const FString& string) {
	TArray<FString> parsed = TArray<FString>();

	string.ParseIntoArray(parsed, TEXT("\n"));

	return parsed;
}