// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/GP_Weapon.h"
#include "GP_GranadeLauncher.generated.h"

class AGP_Projectile;

/**
 * 
 */
UCLASS()
class GAME_PROTOTYPE_API AGP_GranadeLauncher : public AGP_Weapon
{
	GENERATED_BODY()

public:

	AGP_GranadeLauncher();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Granade")
	TSubclassOf <AGP_Projectile> ProjectileClass;
	
protected:

	virtual void startAction() override;

	virtual void stopAction() override;
};
