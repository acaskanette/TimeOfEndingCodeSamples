// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "TOEStoryComponent.generated.h"

class ATOEStoryTrigger;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THE_TIME_OF_ENDING_API UTOEStoryComponent : public USceneComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTOEStoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FString Tag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FColor DialogueColor;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetAndDisplayDialogue(const FString& line, float timeToDisplay, float delayToNextLine, ATOEStoryTrigger* source);

protected:
	FString dialogueLine;
	float dialogueShowTime;
	float dialogueDelayTime;
	float dialogueTimer;
	bool showingDialogue;
	ATOEStoryTrigger* currentDialogueSource;

	UTextRenderComponent* DialogueRender;
};