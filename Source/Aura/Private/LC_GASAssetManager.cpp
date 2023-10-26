// Copyright Curyło Łukasz


#include "LC_GASAssetManager.h"
#include "LC_GameplayTags.h"

ULC_GASAssetManager& ULC_GASAssetManager::Get()
{
	check(GEngine);

	ULC_GASAssetManager* AssetManager = Cast<ULC_GASAssetManager>(GEngine->AssetManager);

	return *AssetManager;
}

void ULC_GASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FLC_GameplayTags::InitializeNativeGameplayTags();
}
