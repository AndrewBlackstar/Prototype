// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GP_Rifle.h"
#include "Game_Prototype/Game_Prototype.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"


AGP_Rifle::AGP_Rifle()
{
	traceLenght = 10000.0f;
	MuzzleSocketName = "SCKT_Muzzle";
}

void AGP_Rifle::startAction()
{
	Super::startAction();

	AActor* CurrentOwner = GetOwner();
	if (IsValid(CurrentOwner))
	{
		FVector eyelocation;
		FRotator eyeRotation;

		CurrentOwner->GetActorEyesViewPoint(eyelocation, eyeRotation);

		FVector ShotDirection = eyeRotation.Vector();
		FVector traceEnd = eyelocation + (ShotDirection * traceLenght);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.bTraceComplex = true;

		FVector traceEndPoint = traceEnd;

		FHitResult hitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, eyelocation, traceEnd, COLLISION_WEAPON, QueryParams);

		if (bHit)
		{
			//make damage
			AActor* HitActor = hitResult.GetActor();
			if (IsValid(HitActor))
			{
				UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, hitResult, CurrentOwner->GetInstigatorController(), this, DamageType);
			}

			traceEndPoint = hitResult.ImpactPoint;

			if (IsValid(ImpactEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, traceEndPoint, hitResult.ImpactNormal.Rotation());
			}
		}

		/*if (bDrawLineTrace)
		{
			DrawDebugLine(GetWorld(), eyelocation, traceEnd, FColor::White, false, 1.0f, 0.0f, 1.0f);
		}*/

		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, CurrentOwnerCharacter->GetMesh(),MuzzleSocketName);
		}

		if (IsValid(TraceEffect))
		{
			USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
			if (IsValid(CharacterMeshComponent))
			{
				FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
				UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);

				if (IsValid(TracerComponent))
				{
					TracerComponent->SetVectorParameter(TraceParamName, traceEndPoint);
				}
			}
			
		}
		
	}
	
}

void AGP_Rifle::stopAction()
{
	Super::stopAction();
}
