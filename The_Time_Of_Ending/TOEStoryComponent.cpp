// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOEStoryComponent.h"
#include "TOEStoryTrigger.h"

// Sets default values for this component's properties
UTOEStoryComponent::UTOEStoryComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// Get a BP class reference for the DialogueWidget and set it as the widget to display as part of the widgetcomponent
	static ConstructorHelpers::FObjectFinder<UClass> dialogueWidgetBPClass(TEXT("Class'/Game/TimeOfEndingAssets/UI/Widgets/DialogueWidget_BP.DialogueWidget_BP_C'"));
	if (dialogueWidgetBPClass.Object != nullptr)
		SetWidgetClass(dialogueWidgetBPClass.Object);

	dialogueWidget = nullptr; // pretty sure I can't initialize it here with the above

	// Set the size of the widget in screen space
	SetDrawSize(FVector2D(750.0f, 300.0f));
	// Set the widget to be displayed in screen coordinates
	Space = EWidgetSpace::Screen;
	// Story tag to allow triggers to send dialogue to this component
	Tag = "None";

	dialogueShowTime = 0;
	dialogueTimer = 0;
	showingDialogue = false;

	// Set visibility to false while not being used
	SetVisibility(false);
}

// Called when the game starts or when spawned
void UTOEStoryComponent::BeginPlay() {
	Super::BeginPlay();

	dialogueWidget = Cast<UDialogueWidget>(GetUserWidgetObject());
	dialogueWidget->InitializePortrait(Portrait, Name, NameColour, BackgroundColour, DialogueColour);
}

// Called every frame
void UTOEStoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Increment timer for dialogue
	if (showingDialogue) {
		dialogueTimer += DeltaTime;

		if (dialogueTimer >= dialogueShowTime) {
			dialogueWidget->ClearDialogue();
			SetVisibility(false);
			showingDialogue = false;
			dialogueTimer = 0;
		}
	}
}

void UTOEStoryComponent::SetAndDisplayDialogue(const FString& line, bool usePortrait, float timeToDisplay) {
	dialogueShowTime = timeToDisplay;

	// Send the string and whether to use the portrait to the DialogueWidget
	dialogueWidget->SetDialogue(line, usePortrait);

	SetVisibility(true);
	showingDialogue = true;
}