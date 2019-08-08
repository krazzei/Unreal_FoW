// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "FogOfWarManager.generated.h"

UCLASS()
class FOGOFWAR_API AFogOfWarManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogOfWarManager();

protected:
	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Fog Of War")
	UStaticMeshComponent *FogMesh;

	UStaticMesh *FogPlane;
	
	UTexture2D *FogTexture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Fog Of War")
	UMaterial *FogMaterial;

	UMaterialInstanceDynamic *FogMatInstance;

	FUpdateTextureRegion2D *FogTextureRegion;

	uint8 *FogBuffer;

	uint8 CurrentColor;
	uint8 StartColor;
	uint8 FinalColor;
	float CurrentTime;

	void UpdateTexture();
	
public:	
	void Tick(float DeltaTime) override;
};
