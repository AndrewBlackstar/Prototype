// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GP_Character.h"


// Sets default values
AGP_Door::AGP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFramecomponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFramecomponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeyZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneCollider->SetupAttachment(CustomRootComponent);
	KeyZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OpenAngle = -90.0f;
	DoorTag = "KeyA";
}

// Called when the game starts or when spawned
void AGP_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &AGP_Door::checkFromPlayer);
	
}

void AGP_Door::checkFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen)
	{
		return;
	}
	
	if (IsValid(OtherActor))
	{
		AGP_Character* OverlappedCharacter = Cast<AGP_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}
		}
	}
}

// Called every frame
void AGP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_Door::OpenDoor()
{
	//FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	//DoorComponent->SetRelativeRotation(NewRotation);

	bIsOpen = true;
	Bp_OpenDoor();
}

