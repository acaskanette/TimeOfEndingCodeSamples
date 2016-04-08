// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Time_Of_Ending.h"
#include "PlayableCharacter.h"
#include "TOELevelScriptActor.h"
#include "TOERespawner.h"


APlayableCharacter::APlayableCharacter()
{
	jumpForce = 500.f;
	GetCharacterMovement()->JumpZVelocity = jumpForce;
	maxCharge = 100.0f;
	currentChargeL2 = 0.0f;
	currentChargeR2 = 0.0f;
	chargeL2 = false;
	chargeR2 = false;

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayableCharacter::Jump);

	InputComponent->BindAction("UseAbilityL2", IE_Released, this, &APlayableCharacter::CastL2Ability);
	InputComponent->BindAction("UseAbilityR2", IE_Released, this, &APlayableCharacter::CastR2Ability);
	InputComponent->BindAction("UseAbilityL2", IE_Pressed, this, &APlayableCharacter::StartChargingAbilityPowerL2);
	InputComponent->BindAction("UseAbilityR2", IE_Pressed, this, &APlayableCharacter::StartChargingAbilityPowerR2);

	InputComponent->BindAction("SwapAbilityL2", IE_Pressed, this, &APlayableCharacter::SwapL2Ability);
	InputComponent->BindAction("SwapAbilityR2", IE_Pressed, this, &APlayableCharacter::SwapR2Ability);
	InputComponent->BindAction("FlipCamera", IE_Pressed, this, &APlayableCharacter::FlipCamera);
	InputComponent->BindAction("Start", IE_Pressed, this, &APlayableCharacter::StartPressed);
	InputComponent->BindAction("Select", IE_Pressed, this, &APlayableCharacter::SelectPressed);
	InputComponent->BindAction("Melee", IE_Pressed, this, &APlayableCharacter::MeleePressed);
	InputComponent->BindAction("Melee", IE_Released, this, &APlayableCharacter::MeleeReleased);
	InputComponent->BindAction("Use", IE_Pressed, this, &APlayableCharacter::UsePressed);

	InputComponent->BindAxis("Move_Right", this, &APlayableCharacter::MoveRight);
	InputComponent->BindAxis("Move_Forward", this, &APlayableCharacter::MoveForward);
	InputComponent->BindAxis("Look_Vertical", this, &APlayableCharacter::SetLookV);
	InputComponent->BindAxis("Look_Horizontal", this, &APlayableCharacter::SetLookH);

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Spawn the AMainCamera into the world the grab its camera component by casting the static class. */
	for (TActorIterator<AMainCamera> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		if (*actorItr != NULL){
			mainCamera = Cast<UCameraComponent>(actorItr->GetComponentByClass(UCameraComponent::StaticClass()));
			break;
		}
	}
	if (mainCamera == NULL)
		mainCamera = Cast<UCameraComponent>(GetWorld()->SpawnActor(AMainCamera::StaticClass())->GetComponentByClass(UCameraComponent::StaticClass()));

	
	/* Cast the animation instance attached to this actor's mesh to be a UPlayableCharacterAnimInstsance */
	animInstance = Cast<UPlayableCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (GetMesh() == NULL)
		UE_LOG(YourLog, Warning, TEXT("Null Instance"));

	/* Initialize variables. */
	lastRotation = GetActorRotation();
	L2AbilityIndex = 0;
	R2AbilityIndex = 1;
	highestUnlockedAbilityIndex = 2;

	abilities.Add(0, EAbilityType::WIND);
	abilities.Add(1, EAbilityType::WATER);
	abilities.Add(2, EAbilityType::EARTH);

	maxHealth = 100;
	currentHealth = maxHealth;
	maxMana = 100;
	currentMana = maxMana;
	manaRegenerationRate = 0.4f;
	timeSinceLastCast = 2.0f;
}

void APlayableCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*if (mainCamera == NULL)
		mainCamera = Cast<UCameraComponent>(GetWorld()->SpawnActor(AMainCamera::StaticClass())->GetComponentByClass(UCameraComponent::StaticClass()));
*/

	//if (!GetMovementComponent()->IsFalling())
		UpdateLookDirection();

	if (chargeL2){

		currentChargeL2 += 25 * DeltaSeconds;

		if (currentChargeL2 > 100.0f)
			currentChargeL2 = 100.0f;

		FString charge = "Charge L2: ";
		charge.AppendInt(currentChargeL2);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Black, charge);
	}
	if (chargeR2){

		currentChargeR2 += 25 * DeltaSeconds;

		if (currentChargeR2 > 100.0f)
			currentChargeR2 = 100.0f;


		FString charge = "Charge R2: ";
		charge.AppendInt(currentChargeR2);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Black, charge);
	}

	currentCharge = FMath::Max(currentChargeL2, currentChargeR2);

	///Updates the UI's Health and Mana displays for the correct character.
	Cast<ATOELevelScriptActor>(GetLevel()->GetLevelScriptActor())->UpdateHealthAndMana(characterName, currentHealth, currentMana, currentTempHealth, currentCharge);
}

void APlayableCharacter::MoveRight(float value)
{
	FVector moveVector(0.f, -1.f, 0.f);

	/** If there is a mainCamera associated with this pawn use its right vector
	  *	as opposed to the right vector of this Actor. Otherwise use this Actor's
	  * right vector. */
	if (mainCamera != NULL)
	{
		FVector cameraRight = mainCamera->GetRightVector();

		AddMovementInput(cameraRight, value);
	}
	else
		AddMovementInput(moveVector, value);
}

void APlayableCharacter::MoveForward(float value)
{
	FVector moveVector(-1.0f, 0.0f, 0.0);

	/** If there is a mainCamera associated with this pawn use its forward vector
	*	as opposed to the forward vector of this Actor. Otherwise use this Actor's
	*   forward vector. */
	if (mainCamera != NULL)
	{
		FVector cameraForward = mainCamera->GetForwardVector();

		AddMovementInput(cameraForward, value);
	}
	else
		AddMovementInput(moveVector, value);
}

void APlayableCharacter::SetLookH(float value)
{
	lookH = InputComponent->GetAxisValue("Look_Horizontal");
}

void APlayableCharacter::SetLookV(float value)
{
	lookV = InputComponent->GetAxisValue("Look_Vertical");
}

void APlayableCharacter::UpdateLookDirection()
{
	FVector lookDirection = lookV * mainCamera->GetForwardVector() + lookH * mainCamera->GetRightVector();

	lookDirection.Z = 0.0f;
	FVector velocity = GetVelocity();

	/* If the actor is not moving. */
	if (velocity.Size() == 0)
	{
		/* Set the animation instance's velocity variables to be 0.0f */
		animInstance->velocityX = 0.0f;
		animInstance->velocityY = 0.0f;

		/* Check whether the player has rotation input on the right stick. */
		if (lookDirection.Size() > 0.0)
		{
			/* Set actor rotation to be the direction the right stick is pointing. */
			lookDirection.Normalize();
			SetActorRotation(FRotationMatrix::MakeFromX(GetActorLocation() - (GetActorLocation() + lookDirection * 5)).Rotator());
		}
		else   //Set the actor's rotation to be the last rotation it had.
			SetActorRotation(lastRotation);
	}
	else   /* If the player is moving. */
	{

		/* Check whether or not the player has rotation input on the right stick. */
		if (lookDirection.Size() > 0.0){
			/* Set actor rotation to be the direction the right stick is pointing. */
			lookDirection.Normalize();
			SetActorRotation(FRotationMatrix::MakeFromX(GetActorLocation() - (GetActorLocation() + lookDirection * 5)).Rotator());
		}
		else
		{ 
			if (!GetMovementComponent()->IsFalling()){
				/* Set the actor rotation to be the direction the actor is moving. */
				SetActorRotation(FRotationMatrix::MakeFromX((GetActorLocation() + velocity * 5) - GetActorLocation()).Rotator());
			}
			else
			{
				//FVector forward = GetActorForwardVector();
				FVector forward = velocity;
				forward.Z = 0;

				SetActorRotation(FRotationMatrix::MakeFromX(GetActorLocation() + forward * 5).Rotator());
			}
		}


		/* Find the velocity which correlates to the actors forward vector.
		  *Essentiallly pass in the direction the actor is moving relative to itself. */
		velocity.Normalize();

		float dot = FVector::DotProduct(velocity, GetActorRotation().Vector());
		float angle = FMath::RadiansToDegrees<float>(FMath::Acos(dot));
		FVector look(1.0, 0.0, 0.0);
		FVector rot = look.RotateAngleAxis(angle, GetActorUpVector());

		FString string("Vector: ");
		string.Append(velocity.ToString());
		string.Append(" / Rotator: ");
		string.Append(GetActorRotation().Vector().ToString());
		string.Append(" / Angle: ");
		string.AppendInt(angle);
		string.Append(" / rotations: ");
		string.Append(rot.ToString());

		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red,string);

		if (velocity.X < 0.0)
			rot.Y = -rot.Y;

		if (animInstance != NULL){
			animInstance->velocityX = rot.X;
			animInstance->velocityY = rot.Y;
		}
	}

	lastRotation = GetActorRotation();
}

void APlayableCharacter::Jump()
{
	Super::Jump();
}

void APlayableCharacter::MeleePressed()
{
	abilityManager->CastAbility(EAbilityType::MELEE, 0.0, this);
	animInstance->isMeleeAttack = true;
}

void APlayableCharacter::MeleeReleased()
{
	animInstance->isMeleeAttack = false;
}


void APlayableCharacter::UsePressed()
{

}

void APlayableCharacter::StartPressed()
{

}

void APlayableCharacter::SelectPressed()
{

}

void APlayableCharacter::RollPressed()
{

}

float APlayableCharacter::GetLastCharge() {
	float tLastCharge = lastCharge;
	lastCharge = 0.0f;
	return tLastCharge;
}

void APlayableCharacter::StartChargingAbilityPowerL2()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Red, "CharginL2");
	chargeL2 = true;
}

void APlayableCharacter::StartChargingAbilityPowerR2()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Red, "CharginR2");
	chargeR2 = true;
}

void APlayableCharacter::CastL2Ability()
{
	if (currentMana > 10 + currentChargeL2 / 2 && timeSinceLastCast >= ABILITY_COOLDOWN)  {

		currentMana -= 10 + currentChargeL2 / 2;
		lastCharge = currentChargeL2;
		timeSinceLastCast = 0.0f;
		abilityManager->CastAbility(abilities[L2AbilityIndex], currentChargeL2, this);
		

	}
	currentChargeL2 = 0.0f;
	chargeL2 = false;

	HandleAttackAnimation(abilities[L2AbilityIndex]);
	
}

void APlayableCharacter::CastR2Ability()
{
	if (currentMana > 10 + currentChargeR2 / 2 && timeSinceLastCast >= ABILITY_COOLDOWN){
		
		currentMana -= 10 + currentChargeR2/2;
		lastCharge = currentChargeR2;
		timeSinceLastCast = 0.0f;
		abilityManager->CastAbility(abilities[R2AbilityIndex], currentChargeR2, this);

	}
	currentChargeR2 = 0.0f;
	chargeR2 = false;

	HandleAttackAnimation(abilities[R2AbilityIndex]);
	

}

void APlayableCharacter::HandleAttackAnimation(EAbilityType type)
{
	switch (type)
	{
	case EAbilityType::EARTH:
		animInstance->isGroundSmash = true;
		break;
	default:
		animInstance->isProjectileAttack = true;
		break;
	}
}

void APlayableCharacter::SwapL2Ability()
{
	if (L2AbilityIndex == highestUnlockedAbilityIndex)
		L2AbilityIndex = 0;
	else
		L2AbilityIndex++;

	Cast<ATOELevelScriptActor>(GetLevel()->GetLevelScriptActor())->UpdateHUD(characterName,EAbilityLocation::L2, abilities[L2AbilityIndex]);
}

void APlayableCharacter::SwapR2Ability()
{
	if (R2AbilityIndex == highestUnlockedAbilityIndex)
		R2AbilityIndex = 0;
	else
		R2AbilityIndex++;

	Cast<ATOELevelScriptActor>(GetLevel()->GetLevelScriptActor())->UpdateHUD(characterName, EAbilityLocation::R2, abilities[R2AbilityIndex]);
}

void APlayableCharacter::FlipCamera() {	
	Cast<AMainCamera>(mainCamera->GetAttachmentRootActor())->FlipCameraAngle();
}

AMainCamera* APlayableCharacter::GetMainCamera() {
	if (mainCamera != NULL)
		return Cast<AMainCamera>(mainCamera->GetAttachmentRootActor());
	else
		return NULL;
}

void APlayableCharacter::OnOutOfHealth() {
	for (TActorIterator<ATOERespawner> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		ActorItr->RespawnPlayers();
}