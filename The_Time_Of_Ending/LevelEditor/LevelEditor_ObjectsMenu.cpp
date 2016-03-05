// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "LevelEditor_ObjectsMenu.h"
#include "../TOEObject.h"

TArray<FString> ULevelEditor_ObjectsMenu::GetAllTileNames() {
	return GetTOEObjectNamesOfSubtype("Blocks");
}

TArray<FString> ULevelEditor_ObjectsMenu::GetAllPropNames() {
	return GetTOEObjectNamesOfSubtype("Props");
}

TArray<FString> ULevelEditor_ObjectsMenu::GetTOEObjectNamesOfSubtype(FString type) {
	auto ObjectLibrary = UObjectLibrary::CreateLibrary(ATOEObject::StaticClass(), true, true);
	ObjectLibrary->LoadBlueprintAssetDataFromPath(TEXT("/Game/TimeOfEndingAssets/Blueprints/BlocksAndProps/" + type));
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);
	UE_LOG(LogTemp, Warning, TEXT("Found objects: %d"), AssetDatas.Num());

	TArray<FString> Names = TArray<FString>();
	for (int32 i = 0; i < AssetDatas.Num(); ++i) {
		FAssetData& AssetData = AssetDatas[i];
		
		// Print paths
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AssetData.ObjectPath.ToString());

		auto name = AssetData.AssetName.ToString();
		Names.Add(name);
	}

	return Names;
}

// TODO: Replace with LoadObject or the thingy I do above to ACTUALLY LOAD, as the issue
// I am having is that it doesn't actually load, therefore the thumbnails only show up if they've been
// opened inside the editor
UTexture2D* ULevelEditor_ObjectsMenu::GetThumbnailTextureFromString(FString name) {
	UObject* package = ANY_PACKAGE;
	return FindObject<UTexture2D>(package, &(name[0]));
}

UClass* ULevelEditor_ObjectsMenu::GetClassFromString(FString name) {
	UObject* package = ANY_PACKAGE;
	return FindObject<UClass>(package, &(name[0]));
}