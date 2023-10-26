// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LC_GASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULC_GASAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static ULC_GASAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
	
};
