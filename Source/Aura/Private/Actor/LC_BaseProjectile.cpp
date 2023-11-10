// Copyright Curyło Łukasz


#include "Actor/LC_BaseProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"

ALC_BaseProjectile::ALC_BaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates=true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Overlap);


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = ProjectileInitialSpeed;
	ProjectileMovementComponent->MaxSpeed=ProjectileMaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileGravity;
}

void ALC_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ALC_BaseProjectile::OnSphereOverlap);

	AudioComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent());
	
}

void ALC_BaseProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,DestructionEffect,GetActorLocation());
	
	if(HasAuthority())
	{
		AudioComponent->Stop();
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		
		Destroy();
	}
	else
	{
		bHit=true;
	}
	
}

void ALC_BaseProjectile::Destroyed()
{
	if(!HasAuthority() && !bHit)
	{
		AudioComponent->Stop();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,DestructionEffect,GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation());
	}
	
	Super::Destroyed();
}
