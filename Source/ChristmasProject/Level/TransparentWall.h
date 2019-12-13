// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransparentWall.generated.h"

UCLASS()
class CHRISTMASPROJECT_API ATransparentWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransparentWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FadeIn();
	void FadeOut();

private:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* m_WallMesh;

	UPROPERTY()
		UMaterialInstanceDynamic* m_WallMat;

	UPROPERTY(VisibleAnywhere)
		float m_MinimumOpacity;

	float m_CurrentOpacity;
	float m_OpacityChange;
};
