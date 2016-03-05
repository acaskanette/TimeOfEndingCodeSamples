// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "FloatingActorTest.h"


// Sets default values
AFloatingActorTest::AFloatingActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingActorTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActorTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();
	float deltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += deltaHeight * 20.0f;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);


}



