// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOEStoryTrigger.h"

#include "PlayableCharacter.h"
#include "TOEStoryComponent.h"
#include "TOEUtilities.h"

// Sets default values
ATOEStoryTrigger::ATOEStoryTrigger() {
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->bGenerateOverlapEvents = true;
	TriggerBox->SetCollisionProfileName(FName(TEXT("OverlapAll")));
	TriggerBox->SetCanEverAffectNavigation(false);
	TriggerBox->AttachParent = RootComponent;

	// Add delegate for overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATOEStoryTrigger::OnTriggerBeginOverlap);

	fileLoaded = false;
	triggered = false;
	currentLine = 0;
}

// Called when the game starts or when spawned
void ATOEStoryTrigger::BeginPlay() {
	Super::BeginPlay();

	xmlDialogueFile = new FXmlFile(FPaths::GameContentDir() + "TimeOfEndingAssets/Dialogue/" + StoryFileName);
	fileLoaded = xmlDialogueFile->IsValid();
	if (fileLoaded) {
		// Get the tags from the XML file and iterate through them, adding them to the search
		FXmlNode* tags = xmlDialogueFile->GetRootNode()->FindChildNode("tags");
		for (const FXmlNode* node = tags->GetFirstChildNode(); node != nullptr; node = node->GetNextNode())
			unfoundStoryTags.Add(node->GetContent());
		// Get the line nodes for later use
		xmlDialogueLines = xmlDialogueFile->GetRootNode()->FindChildNode("lines")->GetChildrenNodes();

		// Iterate through all of the story components in the scene
		for (TObjectIterator<UTOEStoryComponent> itr; itr; ++itr) {
			// Only iterate objects in the world (ignore editor instances)
			if (itr->GetWorld() != GetWorld())
				continue;

			UTOEStoryComponent* comp = *itr;

			// Skip untagged story components; actors that don't use dialogue
			if (comp->Tag.Equals("None"))
				continue;

			int32 foundAt = unfoundStoryTags.Find(comp->Tag);
			// If the story tag of this component is found inside the unfound array, map it and remove it from the unfound array
			if (foundAt != INDEX_NONE) {
				taggedStoryComponents.Add(comp->Tag, comp);
				unfoundStoryTags.RemoveAt(foundAt);
			}
		}

		if (unfoundStoryTags.Num() > 0)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Warning: Some StoryComponents weren't found by trigger: ") + unfoundStoryTags.Num());
	}
	else // if it failed to load
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Failed to load file: " + FPaths::GameContentDir() + "TimeOfEndingAssets/Dialogue/" + StoryFileName));
}

void ATOEStoryTrigger::Destroyed() {
	Super::Destroyed();

	// XML cleanup, unsure if I need to but I did use 'new' so...
	//xmlDialogueFile->Clear();
	//delete xmlDialogueFile;
	//xmlDialogueFile = nullptr;
}

void ATOEStoryTrigger::OnTriggerBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Only matters if the other actor is Rey or Mhambi
	if (OtherActor != nullptr && OtherActor != this && Cast<APlayableCharacter>(OtherActor) != nullptr && OtherComp != nullptr && !triggered) {
		triggered = true;
		if (fileLoaded)
			RunDialogue();
		else
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Trigger won't trigger without text to display."));
	}
}

void ATOEStoryTrigger::RunDialogue() {
	// Check if past the last line, if so, dialogue is over
	if (currentLine >= xmlDialogueLines.Num()) {
		currentLine = 0;
		if (!TriggerOnlyOnce)
			triggered = false;
		return;
	}

	FString storyTag = xmlDialogueLines[currentLine]->GetAttribute("tag");
	float timeToDisplay = FCString::Atof(*xmlDialogueLines[currentLine]->GetAttribute("time"));
	float delayToNextLine = FCString::Atof(*xmlDialogueLines[currentLine]->GetAttribute("delay"));
	bool usePortrait = xmlDialogueLines[currentLine]->GetAttribute("portrait").ToBool();
	FString dialogue = xmlDialogueLines[currentLine]->GetContent();

	// If the story tag wasn't found earlier, end the dialogue instead of attempting to show it (would crash)
	if (taggedStoryComponents[storyTag] == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("OOPS"));
		return;
	}

	// Clear the timer if it exists
	if (dialogueTimer.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(dialogueTimer);
	// Set a timer to call this function again after the current dialogue line is done
	GetWorld()->GetTimerManager().SetTimer(dialogueTimer, this, &ATOEStoryTrigger::RunDialogue, timeToDisplay + delayToNextLine);

	// Tell the story component it has text to display and how long to display it
	taggedStoryComponents[storyTag]->SetAndDisplayDialogue(dialogue, usePortrait, timeToDisplay);
	// Then increment the line number so the next iteration is on the next point in dialogue
	currentLine++;
}