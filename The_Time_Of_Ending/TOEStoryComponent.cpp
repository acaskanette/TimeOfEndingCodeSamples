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

	// Set up the textrender for dialogue
	DialogueRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DialogueRender"));
	DialogueRender->AttachParent = this;
	DialogueRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	DialogueRender->bAbsoluteRotation = true; // Use world rotation so the character moving doesn't affect pointing at screen
	DialogueRender->SetWorldSize(32.0f);
	DialogueColor = FColor::Yellow;

	//ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("Font'/Game/TimeOfEndingAssets/UI/Menus/Hoefler_Render.Hoefler_Render'"));
	//ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Font'/Game/TimeOfEndingAssets/UI/Menus/Hoefler_Mat.Hoefler_Mat'"));

	//DialogueRender->SetFont(Font.Object);
	//DialogueRender->SetTextMaterial(Material.Object);
	//DialogueRender->SetWorldSize(50.0f);

	Tag = "None";

	dialogueLine = "";
	dialogueShowTime = 0;
	dialogueDelayTime = 0;
	dialogueTimer = 0;
	showingDialogue = false;
	currentDialogueSource = nullptr;
}

// Called when the game starts
void UTOEStoryComponent::BeginPlay() {
	Super::BeginPlay();

	DialogueRender->SetTextRenderColor(DialogueColor);

	// Set text render visibility to false when game begins so you can still see it in the editor
	DialogueRender->SetVisibility(false);
}

// Called every frame
void UTOEStoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Increment timer for dialogue
	if (showingDialogue) {
		dialogueTimer += DeltaTime;

		if (dialogueTimer >= dialogueShowTime)
			DialogueRender->SetVisibility(false);

		// End the timer and go to the next point in the dialogue
		if (dialogueTimer >= dialogueShowTime + dialogueDelayTime) {
			showingDialogue = false;
			dialogueTimer = 0;

			currentDialogueSource->RunDialogue();
			//currentDialogueSource = nullptr;
		}
	}

	if (DialogueRender->IsVisible()) {
		// TODO: Show text over time by using dialogueLine and manipulating the text render with SetText

		// Get the camera from player 1 (doesn't matter which character)
		APlayerController* player1 = UGameplayStatics::GetPlayerController(GetOwner(), 0);
		// Get the direction from the actor to the camera to rotate the text render
		FVector dir = player1->PlayerCameraManager->GetCameraLocation() - GetOwner()->GetActorLocation();
		FRotator rot = dir.Rotation();
		DialogueRender->SetWorldRotation(rot);
	}
}

void UTOEStoryComponent::SetAndDisplayDialogue(const FString& line, float timeToDisplay, float delayToNextLine, ATOEStoryTrigger* source) {
	dialogueLine = line;
	dialogueShowTime = timeToDisplay;
	dialogueDelayTime = delayToNextLine;

	// Reference to the dialogue source so the trail can continue
	currentDialogueSource = source;

	GEngine->AddOnScreenDebugMessage(-1, timeToDisplay + delayToNextLine, FColor::Yellow, line);

	DialogueRender->SetText(FText::FromString(dialogueLine));
	DialogueRender->SetVisibility(true);
	showingDialogue = true;
}