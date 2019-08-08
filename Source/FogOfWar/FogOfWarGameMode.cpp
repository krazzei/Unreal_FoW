// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FogOfWarGameMode.h"
#include "FogOfWarPlayerController.h"
#include "FogOfWarCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FogOfWarManager.h"
#include "Engine/World.h"
#include "TextureResource.h"
#include "Engine/Texture2D.h"

AFogOfWarGameMode::AFogOfWarGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFogOfWarPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AFogOfWarGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	auto world = GetWorld();
	// we don't check if world is null because if it is, then something is wrong.
	//world->SpawnActor<AFogOfWarManager>(FVector(0,0,0), FRotator(0,0,0));
	world->SpawnActor<AFogOfWarManager>(FogOfWarManager, FVector(0,0,0), FRotator(0,0,0));
}
