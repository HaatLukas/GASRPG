// Copyright Curyło Łukasz


#include "AbilitySystem/Ability/LC_FireSpellProjectile.h"
#include "Actor/LC_BaseProjectile.h"
#include "Interface/LC_CombatInterface.h"

void ULC_FireSpellProjectile::SpawnProjectile(const FVector& EnemyLocation)
{
	bool bIsOnServer = GetOwningActorFromActorInfo()->HasAuthority();

	if(!bIsOnServer) return;

	ILC_CombatInterface* Interf = Cast<ILC_CombatInterface>(GetAvatarActorFromActorInfo());
	if(Interf)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Interf->GetWeaponTipLocation());
		FRotator CasterRotation = (EnemyLocation - SpawnTransform.GetLocation()).Rotation();
		CasterRotation.Pitch=0.f;
		SpawnTransform.SetRotation(CasterRotation.Quaternion());
		
		ALC_BaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ALC_BaseProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
	Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);
	}
}

void ULC_FireSpellProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
