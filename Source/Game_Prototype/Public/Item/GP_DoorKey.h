// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/GP_Item.h"
#include "GP_DoorKey.generated.h"


class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class GAME_PROTOTYPE_API AGP_DoorKey : public AGP_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:

	AGP_DoorKey();

public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

protected:

	virtual void PickUp(AGP_Character* PickUpActor) override;
	
};
