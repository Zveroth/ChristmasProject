// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparentWall.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ATransparentWall::ATransparentWall() : m_CurrentOpacity(1.0f), m_MinimumOpacity(0.4f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));


	m_WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_WallMesh->SetupAttachment(RootComponent);
	m_WallMesh->SetCollisionProfileName("WDet");
}

// Called when the game starts or when spawned
void ATransparentWall::BeginPlay()
{
	Super::BeginPlay();

	m_WallMat = UMaterialInstanceDynamic::Create(m_WallMesh->GetMaterial(0), this);
	m_WallMesh->SetMaterial(0, m_WallMat);

	SetActorTickEnabled(false);
}

// Called every frame
void ATransparentWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_CurrentOpacity += DeltaTime * m_OpacityChange * 2.0f;

	if (m_OpacityChange == 1.0f)
	{
		if (m_CurrentOpacity >= 1.0f)
		{
			m_CurrentOpacity = 1.0f;
			SetActorTickEnabled(false);
		}
	}
	else
	{
		if (m_CurrentOpacity <= m_MinimumOpacity)
		{
			m_CurrentOpacity = m_MinimumOpacity;
			SetActorTickEnabled(false);
		}
	}

	m_WallMat->SetScalarParameterValue("WallOpacity", m_CurrentOpacity);
}

void ATransparentWall::FadeIn()
{
	SetActorTickEnabled(true);
	m_OpacityChange = 1.0f;
}

void ATransparentWall::FadeOut()
{
	SetActorTickEnabled(true);
	m_OpacityChange = -1.0f;
}