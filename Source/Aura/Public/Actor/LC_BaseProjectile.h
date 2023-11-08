// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LC_BaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURA_API ALC_BaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ALC_BaseProjectile();
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
};

