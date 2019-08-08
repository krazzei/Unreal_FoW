#include "FogOfWarManager.h"
#include <Runtime/Engine/Public/EngineMinimal.h>

AFogOfWarManager::AFogOfWarManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FogPlane = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Engine/BasicShapes/Plane")));
	
	FogMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FogOfWarMesh"));
	FogMesh->SetCollisionProfileName(FName("NoCollision"));
	FogMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 900.0f));
	FogMesh->SetWorldScale3D(FVector(100.0f, 100.0f, 1.0f));
	FogMesh->SetStaticMesh(FogPlane);
	RootComponent = FogMesh;

	FogTextureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, 128, 128);
}

void AFogOfWarManager::BeginPlay()
{
	Super::BeginPlay();
	
	FogTexture = UTexture2D::CreateTransient(128, 128, PF_A8);
	FogTexture->CompressionSettings = TC_Grayscale;
	FogTexture->AddToRoot();

	FogTexture->UpdateResource();

	FogMatInstance = UMaterialInstanceDynamic::Create(FogMaterial, nullptr);
	
	FogMesh->SetMaterial(0, FogMatInstance);

	// TODO: Parametrize the width and height.
	FogBuffer = new uint8[128 * 128];

	for (auto i = 0; i < 128 * 128; ++i)
	{
		// TODO: parametrize the value of unexplored and hidden.
		FogBuffer[i] = 255;
	}
	CurrentColor = 255;
	StartColor = 255;
	FinalColor = 0;
}

void AFogOfWarManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete [] FogBuffer;
}

void AFogOfWarManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += 10 * DeltaTime;
	
	CurrentColor = FMath::Lerp(StartColor, FinalColor, CurrentTime / 10);
	
	if (CurrentTime >= 10.f)
	{
		const auto Temp = FinalColor;
		FinalColor = StartColor;
		StartColor = Temp;
		CurrentTime = 0.0f;
	}
	
	if (GFrameNumber % 3 == 0)
	{
		UpdateTexture();
	}
}

void AFogOfWarManager::UpdateTexture()
{
	for (auto i = 0; i < 128 * 128; ++i)
	{
		FogBuffer[i] = CurrentColor;
	}

	FogTexture->UpdateTextureRegions(0, 1, FogTextureRegion, 128, 1, FogBuffer);
	FogMatInstance->SetTextureParameterValue(FName("DynamicTexture"), FogTexture);
}
