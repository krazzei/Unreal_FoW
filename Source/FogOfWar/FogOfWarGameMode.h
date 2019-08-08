// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FogOfWarManager.h"
#include "FogOfWarGameMode.generated.h"

UCLASS(minimalapi)
class AFogOfWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFogOfWarGameMode();
	
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UPROPERTY(EditDefaultsOnly, Category = "Fog Of War")
	TSubclassOf<AFogOfWarManager> FogOfWarManager;
};
