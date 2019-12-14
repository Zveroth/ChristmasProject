// Fill out your copyright notice in the Description page of Project Settings.


#include "Santa.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ASanta::ASanta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SantaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SantaMesh->SetupAttachment(RootComponent);
	SantaMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Santa_Mesh")).Object);
	SantaMesh->SetCollisionProfileName("SDet");
}

// Called when the game starts or when spawned
void ASanta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASanta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

