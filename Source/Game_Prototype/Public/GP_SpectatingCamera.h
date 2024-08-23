// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM(Blueprintable)
enum EGP_SpectattingCameraType : uint8
{
	CameraTypoe_None UMETA(DisplayName = "None"),
	CameraType_ViCtory UMETA(DisplayName = "Victory"),
	CameraType_GameOver UMETA(DisplayName = "Game Over")
};

UCLASS()
class GAME_PROTOTYPE_API AGP_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
	UStaticMeshComponent* spectatingCameraComponent;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpectetingCamera")
	EGP_SpectattingCameraType CameraType;

public:	
	// Sets default values for this actor's properties
	AGP_SpectatingCamera();

	EGP_SpectattingCameraType GetCameraType() { return CameraType; };
};
