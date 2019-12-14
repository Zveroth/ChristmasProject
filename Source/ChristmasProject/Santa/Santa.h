// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Santa.generated.h"

UCLASS()
class CHRISTMASPROJECT_API ASanta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASanta();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SantaMesh;
};
