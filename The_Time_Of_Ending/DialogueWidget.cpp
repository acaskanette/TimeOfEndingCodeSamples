// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "DialogueWidget.h"
#include "Kismet/KismetStringLibrary.h"

UDialogueWidget::UDialogueWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {
	TextScrollSpeed = 0.03F;
}

//void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
//	UUserWidget::NativeTick(MyGeometry, DeltaTime);
//  In case I need to fix it again, would probably use this function
//  I can't test it on my bad computer in the first place so can't know if this fixed it, either way...
//}

void UDialogueWidget::ClearDialogue_Implementation() {
	// Called by the story component when its timer is up, clears the text to ensure
	// the game doesn't show the full string accidentally before showing the scrolling text
	DialogueText = FText::FromString("");
	showingDialogue = false;
}

void UDialogueWidget::StartFadeText_Implementation() {
	if (!showingDialogue) {
		// Set a looping timer for the fading text
		GetWorld()->GetTimerManager().SetTimer(dialogueTimer, this, &UDialogueWidget::FadeText, TextScrollSpeed, true, 0.0f);
		showingDialogue = true;
	}
}

void UDialogueWidget::FadeText() {
	if (LettersRemaining >= 0) {
		FString partialDialogueString = UKismetStringLibrary::GetSubstring(DialogueString, 0, DialogueString.Len() - LettersRemaining);
		DialogueText = FText::FromString(partialDialogueString);
		LettersRemaining--;
	}
	else {
		// Clear the timer so it stops looping once done
		GetWorld()->GetTimerManager().ClearTimer(dialogueTimer);
	}
}