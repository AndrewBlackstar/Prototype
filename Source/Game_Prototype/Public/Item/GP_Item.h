// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_Character.h"
#include "GP_Item.generated.h"

class USphereComponent;

UCLASS()
class GAME_PROTOTYPE_API AGP_Item : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
	USphereComponent* MainColliderComponent;

public:	
	// Sets default values for this actor's properties
	AGP_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PickUp(AGP_Character* PickUpActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_PickUP(AGP_Character* PickUpActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
