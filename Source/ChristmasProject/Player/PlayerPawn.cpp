// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = m_PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capusle"));
	m_PlayerCapsule->SetupAttachment(RootComponent);
	m_PlayerCapsule->InitCapsuleSize(25.0f, 50.0f);
	m_PlayerCapsule->SetCollisionProfileName("BlockAll");

	m_PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_PlayerMesh->SetupAttachment(RootComponent);
	m_PlayerMesh->RelativeScale3D = FVector(0.25f, 0.25f, 1.0f);
	m_PlayerMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube")).Object);
	
	m_CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	m_CameraArm->SetupAttachment(RootComponent);
	m_CameraArm->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	m_CameraArm->TargetArmLength = 1500.0f;
	m_CameraArm->bDoCollisionTest = false;
	m_CameraArm->CameraLagSpeed = 1.5f;

	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_PlayerCamera->SetupAttachment(m_CameraArm, USpringArmComponent::SocketName);
	m_PlayerCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	m_PlayerCamera->SetFieldOfView(60.0f);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MovementDir != FVector::ZeroVector)
	{
		m_PlayerMesh->SetWorldRotation(MovementDir.Rotation());
		AddActorWorldOffset(MovementDir * 300.0f * DeltaTime, true);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APlayerPawn::SetXMovement);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerPawn::SetYMovement);
}

void APlayerPawn::SetXMovement(float MS)
{
	MovementDir.X = MS;
}

void APlayerPawn::SetYMovement(float MS)
{
	MovementDir.Y = MS;
}