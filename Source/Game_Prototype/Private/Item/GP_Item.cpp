// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GP_Item.h"
#include "Components/SphereComponent.h"
#include "GP_Character.h"


// Sets default values
AGP_Item::AGP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


}

// Called when the game starts or when spawned
void AGP_Item::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AGP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_Item::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AGP_Character* OverlapedCharacter = Cast<AGP_Character>(OtherActor);
		if (IsValid(OverlapedCharacter))
		{
			PickUp(OverlapedCharacter);
		}
	}
}

void AGP_Item::PickUp(AGP_Character* PickUpActor)
{
	BP_PickUP(PickUpActor);
}
