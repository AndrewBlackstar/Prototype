// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_Character.h"
#include "GP_launchpad.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GAME_PROTOTYPE_API AGP_launchpad : public AActor
{
	GENERATED_BODY()
	
protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* launchMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* launchZoneCollider;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "launcher")
	float launchForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "launcher")
	FName launchTag;

public:	
	// Sets default values for this actor's properties
	AGP_launchpad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void checkFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void launcPLayer(AGP_Character* character);

};
