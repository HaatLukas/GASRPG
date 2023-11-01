// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "LC_InputDataAsset.h"
#include "LC_EnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULC_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const ULC_InputDataAsset* DataAsset,UserClass* Object, PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void ULC_EnhancedInputComponent::BindAbilityActions(const ULC_InputDataAsset* DataAsset, UserClass* Object, PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	checkf(DataAsset, TEXT("Data Asset for InputDataAsset not Found"));

	for (const FLC_InputAction& Action : DataAsset->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}


}


