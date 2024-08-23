// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_MovablePlatform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class GAME_PROTOTYPE_API AGP_MovablePlatform : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "components")
	UStaticMeshComponent* PlatformMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
	USceneComponent* CustomRootComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	bool bIsGoinUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MinHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MaxHeight;

	
public:	
	// Sets default values for this actor's properties
	AGP_MovablePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
