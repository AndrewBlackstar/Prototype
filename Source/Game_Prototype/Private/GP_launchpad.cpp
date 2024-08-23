// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_launchpad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GP_Character.h"

// Sets default values
AGP_launchpad::AGP_launchpad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	launchMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchMesh"));
	launchMeshComponent->SetupAttachment(CustomRootComponent);

	launchZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchZoneCollider"));
	launchZoneCollider->SetupAttachment(CustomRootComponent);
	launchZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	launchZoneCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	launchZoneCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	launchForce = 1000.0f;
	launchTag = "KeyLaunch";
}

// Called when the game starts or when spawned
void AGP_launchpad::BeginPlay()
{
	Super::BeginPlay();
	launchZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &AGP_launchpad::checkFromPlayer);
	
}

void AGP_launchpad::checkFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AGP_Character* OverlappedCharacter = Cast<AGP_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(launchTag))
			{
				launcPLayer(OverlappedCharacter);
			}
		}
	}

}

// Called every frame
void AGP_launchpad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_launchpad::launcPLayer(AGP_Character* character)
{
	FVector launchdirection = FVector(0, 0, 1);
	
	character->LaunchCharacter(launchdirection * launchForce, true, true);
}

