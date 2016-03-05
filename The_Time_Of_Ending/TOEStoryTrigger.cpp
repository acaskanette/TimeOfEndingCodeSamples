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

	FString fileContents;
	// Load the relevant file to a string
	fileLoaded = UTOEUtilities::LoadTextFileToString(StoryFilePath.FilePath, fileContents);
	if (fileLoaded) {
		// Parse the string by "\n"
		fileContents.ParseIntoArray(fileLines, TEXT("\n"));
		// The first line is what story tags are associated with this trigger
		fileLines[0].ParseIntoArray(unfoundStoryTags, TEXT(","));
		// Remove the last element of the line because FUCK \n SERIOUSLY I CAN'T TRIM IT AND IT CAUSED 3 HOURS OF HEADACHE BECAUSE ONE ELEMENT OF THE UNFOUND ARRAY HAD A NEWLINE IN IT
		unfoundStoryTags.Pop(true);
		// Delete this line as it's no longer needed
		fileLines.RemoveAt(0);

		// Iterate through all of the story components in the scene
		for (TObjectIterator<UTOEStoryComponent> itr; itr; ++itr) {
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

		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Dialogue lines: ") + fileLines.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Participants: ") + taggedStoryComponents.Num());

		if (unfoundStoryTags.Num() > 0) {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Some StoryComponents weren't found by trigger: ") + unfoundStoryTags.Num());
			// TODO: Post-spawn finding of storytags
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Warning: Don't go into that trigger, I haven't added post-spawn finding of storytags, currently only at beginplay. Might crash!"));
		}
	}
	else // if it failed to load
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Failed to load file: " + StoryFilePath.FilePath));
}

void ATOEStoryTrigger::OnTriggerBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Only matters if the other actor is Rey or Mhambi
	if (OtherActor != nullptr && OtherActor != this && Cast<APlayableCharacter>(OtherActor) != nullptr && OtherComp != nullptr && !triggered) {
		triggered = true;
		if (fileLoaded) {
			RunDialogue();
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Trigger don't trigger without text to display."));
	}
}

void ATOEStoryTrigger::RunDialogue() {
	// Check if past the last line, if so, dialogue is over
	if (currentLine >= fileLines.Num()) {
		currentLine = 0;
		if (!TriggerOnlyOnce)
			triggered = false;
		return;
	}

	// Parse the line by "-" to get the story tag, display time, and actual dialogue
	TArray<FString> line;
	fileLines[currentLine].ParseIntoArray(line, TEXT("-"));

	FString storyTag = line[0];
	float timeToDisplay = FCString::Atof(*line[1]);
	float delayToNextLine = FCString::Atof(*line[2]);
	FString dialogue = line[3];

	// If the story tag wasn't found earlier, end the dialogue instead of attempting to show it (would crash)
	if (taggedStoryComponents[storyTag] == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("OOPS"));
		return;
	}

	// Tell the story component what to display
	taggedStoryComponents[storyTag]->SetAndDisplayDialogue(dialogue, timeToDisplay, delayToNextLine, this);

	// Increment current line
	currentLine++;
}