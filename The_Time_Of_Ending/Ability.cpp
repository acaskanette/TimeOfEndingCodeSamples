// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "Ability.h"
#include "Prop.h"
#include "PlayableCharacter.h"


// Sets default values
AAbility::AAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	SetRootComponent(root);
	root->SetVisibility(false);
	root->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	sphereComponent->AttachTo(RootComponent);
	//sphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//Creates a delegate for the OnHitEvent and adds it to the sphere component.
	sphereComponent->bGenerateOverlapEvents = true;
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAbility::OnBeginOverlap);

	chargeAmount = 0.0f;
	

}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();

	caster = this->GetInstigator();

	APlayableCharacter* character = Cast<APlayableCharacter>(caster);

	if (character) {
		chargeAmount = character->GetLastCharge();
	}
	else {
		chargeAmount = 0.0f;
	}
	chargeDamageMultiplier = 1.0f;

}

// Called every frame
void AAbility::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAbility::OnBeginOverlap_Implementation(AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString("Overlapped"));
	
	ATOECharacter* character = Cast<ATOECharacter>(OtherActor);

	if (character != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString("Hit"));
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, character->GetName());
		character->OnAbilityOverlap(this);
	}

	else {
		AProp* prop = Cast<AProp>(OtherActor);

		if (prop != NULL)
		{
			prop->OnAbilityOverlap(this);
		}
	}

	character = NULL;
}