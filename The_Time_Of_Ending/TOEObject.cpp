// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "TOEObject.h"


// Sets default values
ATOEObject::ATOEObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATOEObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATOEObject::onDestroy(){

}

// Called every frame
void ATOEObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATOEObject::onOverlap(AActor other){

}

