// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GP_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "GP_Character.h"

AGP_DoorKey::AGP_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyTag = "KeyA";
}

void AGP_DoorKey::PickUp(AGP_Character* PickUpActor)
{
	Super::PickUp(PickUpActor);

	PickUpActor->AddKey(KeyTag);
	Destroy();
}
