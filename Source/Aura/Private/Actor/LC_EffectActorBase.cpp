// Copyright Curyło Łukasz


#include "Actor/LC_EffectActorBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
ALC_EffectActorBase::ALC_EffectActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(Root);
}

void ALC_EffectActorBase::ApplyEffectToTarget(AActor* ActorTarget, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// How to apply Gameplay Effect to a Target?

	// 1. Get AbilitySystemComponent of that target to see if it should do anything
	// 2. Check if we have a valid GameplayEffect to choose from
	// 3. To apply GameplayEffect we can choose 4 options SpecToSelf,SpecToTarget,ToSelf,ToTarget, choose any
	// 4. To meet the requirements I need to make EffectSpecHandle.
	// 4.1 To make a EffectSpecHandle I need EffectContextHandle
	// 4.2 To make that I need to use MakeEffectContext() for the Target that implements ASC
	// 4.2.1 After that I need to say what is the causer of the effect
	// 4.3 Then To make EffectSpecHandle use MakeOutgoingSpec and meet the requirements
	// 5. To apply the effect, use ApplyGameplayEffectXYZ and derefernce to the spechandle.data.get()

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorTarget);
	if (TargetASC)
	{
		checkf(GameplayEffectClass, TEXT("Set proper GameplayEffectClass in BP"));
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if (bIsInfinite && InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}


}

void ALC_EffectActorBase::ApplyEffectsToTarget(AActor* ActorTarget, TArray<TSubclassOf<UGameplayEffect>> GE_Array)
{
	for (auto Effect : GE_Array)
	{
		ApplyEffectToTarget(ActorTarget, Effect);
	}
}

void ALC_EffectActorBase::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyInstantEffects(TargetActor);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyDurationEffects(TargetActor);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyInfiniteEffects(TargetActor);
	}
}



void ALC_EffectActorBase::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyInstantEffects(TargetActor);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyDurationEffects(TargetActor);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyInstantEffects(TargetActor);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;


		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}

}

void ALC_EffectActorBase::ApplyInfiniteEffects(AActor* TargetActor)
{
	if (InfiniteGEClasses.Num() > 0)
	{
		ApplyEffectsToTarget(TargetActor, InfiniteGEClasses);
	}
	else
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void ALC_EffectActorBase::ApplyDurationEffects(AActor* TargetActor)
{
	if (DurationGEClasses.Num() > 0)
	{
		ApplyEffectsToTarget(TargetActor, DurationGEClasses);
	}
	else
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
}

void ALC_EffectActorBase::ApplyInstantEffects(AActor* TargetActor)
{
	if (InstantGEClasses.Num() > 0)
	{
		ApplyEffectsToTarget(TargetActor, InstantGEClasses);
	}
	else
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
}



