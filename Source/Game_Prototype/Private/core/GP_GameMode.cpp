// Fill out your copyright notice in the Description page of Project Settings.


#include "core/GP_GameMode.h"
#include "GP_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void AGP_GameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AGP_GameMode::Victory(AGP_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void AGP_GameMode::GameOver(AGP_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Character->DetachFromControllerPendingDestroy();
	Character->SetLifeSpan(5.0f);

	BP_GameOver(Character);
}
