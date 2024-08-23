// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/GP_Weapon.h"
#include "GP_Rifle.generated.h"


class UParticleSystem;
/**
 * 
 */
UCLASS()
class GAME_PROTOTYPE_API AGP_Rifle : public AGP_Weapon
{
	GENERATED_BODY()

public:

	AGP_Rifle();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lineTrace|Debug")
	bool bDrawLineTrace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lineTrace")
	float traceLenght;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	FName TraceParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* MuzzleEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TraceEffect;

protected:

	virtual void startAction() override;

	virtual void stopAction() override;
};
