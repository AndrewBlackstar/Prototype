// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GP_GameMode.generated.h"

class AGP_Character;
class AGP_SpectatingCamera;

/**
 * 
 */
UCLASS()
class GAME_PROTOTYPE_API AGP_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SpectatingCamera")
	AGP_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "SpectatingCamera")
	AGP_SpectatingCamera* GameOverCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Victory(AGP_Character* Character);

	UFUNCTION()
	void GameOver(AGP_Character* Character);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AGP_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AGP_Character* Character);
};
