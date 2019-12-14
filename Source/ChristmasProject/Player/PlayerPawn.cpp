// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Level/TransparentWall.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capusle"));
	PlayerCapsule->SetupAttachment(RootComponent);
	PlayerCapsule->InitCapsuleSize(25.0f, 50.0f);
	PlayerCapsule->SetCollisionProfileName("BlockAll");

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PlayerMesh->SetupAttachment(RootComponent);
	PlayerMesh->RelativeScale3D = FVector(0.25f, 0.25f, 1.0f);
	PlayerMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Player_Mesh")).Object);
	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	CameraArm->TargetArmLength = 1500.0f;
	CameraArm->bDoCollisionTest = false;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 4.0f;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	PlayerCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	PlayerCamera->SetFieldOfView(60.0f);

	WallDetection = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WallDetection"));
	WallDetection->SetupAttachment(RootComponent);
	WallDetection->InitCapsuleSize(200.0f, 200.0f);
	WallDetection->SetCollisionProfileName("WDet");

	FScriptDelegate DummyWB;
	DummyWB.BindUFunction(this, FName("WallBeginOverlap"));
	WallDetection->OnComponentBeginOverlap.AddUnique(DummyWB);

	FScriptDelegate DummyWE;
	DummyWE.BindUFunction(this, FName("WallEndOverlap"));
	WallDetection->OnComponentEndOverlap.AddUnique(DummyWE);

	SantaDetection = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SantaDetection"));
	SantaDetection->SetupAttachment(RootComponent);
	SantaDetection->InitCapsuleSize(100.0f, 100.0f);
	SantaDetection->SetCollisionProfileName("SDet");

	FScriptDelegate DummySB;
	DummySB.BindUFunction(this, FName("SantaBeginOverlap"));
	WallDetection->OnComponentBeginOverlap.AddUnique(DummySB);

	FScriptDelegate DummySE;
	DummySE.BindUFunction(this, FName("SantaEndOverlap"));
	WallDetection->OnComponentEndOverlap.AddUnique(DummySE);
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
		PlayerMesh->SetWorldRotation(MovementDir.Rotation());
		MovementDir.Normalize();
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


void APlayerPawn::WallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATransparentWall* Wall = Cast<ATransparentWall>(OtherActor))
		Wall->FadeOut();
}

void APlayerPawn::WallEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATransparentWall* Wall = Cast<ATransparentWall>(OtherActor))
		Wall->FadeIn();
}

void APlayerPawn::SantaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bCloseToSanta = true;
}

void APlayerPawn::SantaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCloseToSanta = false;
}