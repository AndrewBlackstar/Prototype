// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GP_GranadeLauncher.h"
#include "Weapons/GP_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"



AGP_GranadeLauncher::AGP_GranadeLauncher()
{
	MuzzleSocketName = "SCKT_Muzzle";
}

void AGP_GranadeLauncher::startAction()
{
	Super::startAction();
	
	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			AGP_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AGP_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}
	
}

void AGP_GranadeLauncher::stopAction()
{
	Super::stopAction();
}
