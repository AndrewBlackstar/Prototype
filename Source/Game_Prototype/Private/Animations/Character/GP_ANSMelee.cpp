// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/GP_ANSMelee.h"
#include "GP_Character.h"

void UGP_ANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AActor* characterActor = MeshComp->GetOwner();
	if (IsValid(characterActor))
	{
		AGP_Character* Character = Cast<AGP_Character>(characterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UGP_ANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AActor* characterActor = MeshComp->GetOwner();
	if (IsValid(characterActor))
	{
		AGP_Character* Character = Cast<AGP_Character>(characterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
		}
	}
}
