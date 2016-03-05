// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GameFramework/Actor.h"
#include "TOEStoryTrigger.generated.h"

UENUM(BlueprintType)
enum class EStoryTriggerType : uint8 {
	Dialogue, Tutorial
};

UCLASS()
class THE_TIME_OF_ENDING_API ATOEStoryTrigger : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATOEStoryTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UBoxComponent* TriggerBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EStoryTriggerType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool TriggerOnlyOnce;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FFilePath StoryFilePath;

	void RunDialogue();

protected:
	UFUNCTION()
		void OnTriggerBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// The file, split by lines
	TArray<FString> fileLines;
	// References to StoryComponents on characters/etc, for easy sending of dialogue / other messages
	TMap<FString, class UTOEStoryComponent*> taggedStoryComponents;
	TArray<FString> unfoundStoryTags;

	int32 currentLine;
	bool fileLoaded, triggered;
};
