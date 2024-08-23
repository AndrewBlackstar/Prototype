// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/GP_ANEnableAction.h"
#include "GP_Character.h"

void UGP_ANEnableAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AActor* characterActor = MeshComp->GetOwner();
	if (IsValid(characterActor))
	{
		AGP_Character* Character = Cast<AGP_Character>(characterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeState(false);
		}
	}
}
