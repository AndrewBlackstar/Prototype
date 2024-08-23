// Fill out your copyright notice in the Description page of Project Settings.


#include "core/GP_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "GP_Character.h"
#include "Core/GP_GameMode.h"

// Sets default values
AGP_VictoryZone::AGP_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	victoryzonecomponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZone"));
	RootComponent = victoryzonecomponent;
	victoryzonecomponent->SetBoxExtent(FVector(100.0f));

}

// Called when the game starts or when spawned
void AGP_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeRef = Cast<AGP_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AGP_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeRef))
	{
		AGP_Character* GPCharacter = Cast<AGP_Character>(OtherActor);
		if (IsValid(GPCharacter))
		{
			GameModeRef->Victory(GPCharacter);
		}
	}
}

