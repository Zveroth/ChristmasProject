// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CHRISTMASPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* PlayerCapsule;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* WallDetection;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* SantaDetection;

	FVector MovementDir;

	void SetXMovement(float MS);
	void SetYMovement(float MS);

	UFUNCTION()
		void WallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void WallEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SantaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void SantaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bCloseToSanta;
};
