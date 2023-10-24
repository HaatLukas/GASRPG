// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LC_CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULC_CombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ILC_CombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

};
