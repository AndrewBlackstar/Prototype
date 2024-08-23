// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GP_Weapon.h"
#include "GameFramework/Character.h"

// Sets default values
AGP_Weapon::AGP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;
}

// Called when the game starts or when spawned
void AGP_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_Weapon::startAction()
{
	BP_startAction();
}

void AGP_Weapon::stopAction()
{
	BP_StopAction();
}

void AGP_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
	
}

