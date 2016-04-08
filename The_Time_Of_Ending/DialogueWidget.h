// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 *
 */
UCLASS()
class THE_TIME_OF_ENDING_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDialogueWidget(const FObjectInitializer& ObjectInitializer);

	//virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Portrait")
		void InitializePortrait(UTexture2D* portrait, const FString& speakerName, FLinearColor nameColour, FLinearColor backgroundColour, FLinearColor dialogueColour);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue")
		void SetDialogue(const FString& dialogue, bool usePortrait = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dialogue")
		void ClearDialogue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dialogue")
		void StartFadeText();

	void InitializePortrait_Implementation(UTexture2D* portrait, const FString& speakerName, FLinearColor nameColour, FLinearColor backgroundColour, FLinearColor dialogueColour) {}
	void SetDialogue_Implementation(const FString& dialogue, bool usePortrait) {}
	void ClearDialogue_Implementation();
	void StartFadeText_Implementation();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FString DialogueString;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FText DialogueText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		int32 LettersRemaining;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		float TextScrollSpeed;

	FTimerHandle dialogueTimer;
	bool showingDialogue;

	void FadeText();
};