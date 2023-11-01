// Copyright Curyło Łukasz


#include "Input/LC_InputDataAsset.h"

const UInputAction* ULC_InputDataAsset::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (FLC_InputAction AInputAction : AbilityInputActions)
	{
		if (AInputAction.InputAction && AInputAction.InputTag.MatchesTagExact(InputTag))
		{
			return AInputAction.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on Input Config [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
