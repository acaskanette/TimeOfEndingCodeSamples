// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/WidgetComponent.h"
#include "DialogueWidget.h"
#include "TOEStoryComponent.generated.h"

class ATOEStoryTrigger;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THE_TIME_OF_ENDING_API UTOEStoryComponent : public UWidgetComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTOEStoryComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// The tag used by triggers to find this story component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FString Tag;

	// The name of the speaker to display in the portrait
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portrait")
		FString Name;

	// The portrait image
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portrait")
		UTexture2D* Portrait;

	// The font colour for the name in the portrait
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portrait")
		FLinearColor NameColour;

	// The border colour for the text in the portrait
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portrait")
		FLinearColor BackgroundColour;

	// The dialogue text colour
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portrait")
		FLinearColor DialogueColour;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetAndDisplayDialogue(const FString& line, bool usePortrait, float timeToDisplay);
protected:
	float dialogueShowTime;
	float dialogueTimer;
	bool showingDialogue;

	UDialogueWidget* dialogueWidget;
};