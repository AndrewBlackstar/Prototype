// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_MovablePlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGP_MovablePlatform::AGP_MovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomRootComponent);

	bIsGoinUp = true;
	speed = 10.0f;
	MinHeight = 0.0F;
	MaxHeight = 50.0f;

}

// Called when the game starts or when spawned
void AGP_MovablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AGP_MovablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AGP_MovablePlatform::Move()
{
	FVector UpDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());
	if (bIsGoinUp)
	{
		UpDirection = UpDirection;
	}
	else
	{
		UpDirection = UpDirection * -1;
	}

	FVector CurrentVelocity = UpDirection * speed;
	FVector NewPosition = GetActorLocation() + CurrentVelocity;
	SetActorLocation(NewPosition);

	if ((bIsGoinUp && GetActorLocation().Z >= MaxHeight) || (!bIsGoinUp && GetActorLocation().Z <=MinHeight))
	{
		bIsGoinUp = !bIsGoinUp;
	}
}
