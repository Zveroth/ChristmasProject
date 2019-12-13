// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ChristmasProjectGameModeBase.h"
#include "Player/PlayerPawn.h"



AChristmasProjectGameModeBase::AChristmasProjectGameModeBase(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DefaultPawnClass = APlayerPawn::StaticClass();
}