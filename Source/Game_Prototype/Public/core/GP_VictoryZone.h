// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_VictoryZone.generated.h"

class UBoxComponent;
class AGP_GameMode;

UCLASS()
class GAME_PROTOTYPE_API AGP_VictoryZone : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* victoryzonecomponent;

protected:

	AGP_GameMode* GameModeRef;
	
public:	
	// Sets default values for this actor's properties
	AGP_VictoryZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
