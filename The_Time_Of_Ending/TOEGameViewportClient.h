// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "TOEGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class THE_TIME_OF_ENDING_API UTOEGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
	
	virtual void UpdateActiveSplitscreenType() override;
	
};
