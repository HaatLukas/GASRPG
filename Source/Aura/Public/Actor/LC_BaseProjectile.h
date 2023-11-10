// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "LC_BaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class AURA_API ALC_BaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ALC_BaseProjectile();
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	UPROPERTY(EditDefaultsOnly)
	float ProjectileInitialSpeed = 550.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileMaxSpeed = 550.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileGravity = 0.f;
	
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	bool bHit=false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> DestructionEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AudioComponent;

	virtual void Destroyed() override;
	
};

