// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparentWall.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ATransparentWall::ATransparentWall() : CurrentOpacity(1.0f), MinimumOpacity(0.4f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));


	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WallMesh->SetupAttachment(RootComponent);
	WallMesh->SetCollisionProfileName("WDet");
}

// Called when the game starts or when spawned
void ATransparentWall::BeginPlay()
{
	Super::BeginPlay();

	WallMat = UMaterialInstanceDynamic::Create(WallMesh->GetMaterial(0), this);
	WallMesh->SetMaterial(0, WallMat);

	SetActorTickEnabled(false);
}

// Called every frame
void ATransparentWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentOpacity += DeltaTime * OpacityChange * 2.0f;

	if (OpacityChange == 1.0f)
	{
		if (CurrentOpacity >= 1.0f)
		{
			CurrentOpacity = 1.0f;
			SetActorTickEnabled(false);
		}
	}
	else
	{
		if (CurrentOpacity <= MinimumOpacity)
		{
			CurrentOpacity = MinimumOpacity;
			SetActorTickEnabled(false);
		}
	}

	WallMat->SetScalarParameterValue("WallOpacity", CurrentOpacity);
}

void ATransparentWall::FadeIn()
{
	SetActorTickEnabled(true);
	OpacityChange = 1.0f;
}

void ATransparentWall::FadeOut()
{
	SetActorTickEnabled(true);
	OpacityChange = -1.0f;
}