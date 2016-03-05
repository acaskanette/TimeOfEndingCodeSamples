// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "LevelEditor_ObjectsMenu.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API ULevelEditor_ObjectsMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Utility")
		TArray<FString> GetAllTileNames();

	UFUNCTION(BlueprintCallable, Category = "Utility")
		TArray<FString> GetAllPropNames();

	UFUNCTION(BlueprintCallable, Category = "Utility")
		UTexture2D* GetThumbnailTextureFromString(FString name);

	UFUNCTION(BlueprintCallable, Category = "Utility")
		UClass* GetClassFromString(FString name);

private:
	TArray<FString> GetTOEObjectNamesOfSubtype(FString type);
};
