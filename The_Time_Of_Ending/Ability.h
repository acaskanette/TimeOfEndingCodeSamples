// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	WIND,
	WATER,
	EARTH,
	FIRE,
	SPECIAL,
	MELEE
};


UCLASS()
class THE_TIME_OF_ENDING_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:
		
	// Sets default values for this actor's properties
	AAbility();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	
	// Ability Properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Info", Meta = (DisplayName = "Damage", ExposeOnSpawn = true))
		float damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Info", Meta = (DisplayName = "element", ExposeOnSpawn = true))
		EAbilityType element;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Info", Meta = (DisplayName = "caster", ExposeOnSpawn = true))
		AActor* caster;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Info", Meta = (DisplayName = "charge amount", ExposeOnSpawn = true))
		float chargeAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
		float chargeDamageMultiplier;

	// Collision Properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
	USphereComponent* sphereComponent;

	USphereComponent* root;

	// Ability Methods
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void OnBeginOverlap(AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
