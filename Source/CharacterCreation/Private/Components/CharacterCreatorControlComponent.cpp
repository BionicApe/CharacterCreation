// Created by Bionic Ape. All Rights Reserved.


#include "Components/CharacterCreatorControlComponent.h"
#include "CharacterCreator.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


void UCharacterCreatorControlComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreatorControlComponent, CharacterCreators);
}
//
//bool UCharacterCreatorControlComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
//{
//	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
//	WroteSomething |= Channel->ReplicateSubobjectList(CharacterCreators, *Bunch, *RepFlags);
//	return WroteSomething;
//}

void UCharacterCreatorControlComponent::AddCharacterCreator(UCharacterCreator* NewCharacterCreator)
{
	CharacterCreators.AddUnique(NewCharacterCreator);
}


void UCharacterCreatorControlComponent::SetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	ServerSetAttributeValue(NewCharacterCreator, CCAttribute, NewValue);
}

void UCharacterCreatorControlComponent::ServerSetAttributeValue_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetAttributeValue(CCAttribute, NewValue);
	}
}

void UCharacterCreatorControlComponent::SetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit)
{
	ServerSetOutfit(CharacterCreator, SelectedOutfit);
}

void UCharacterCreatorControlComponent::ServerSetOutfit_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetOutfit(SelectedOutfit);
	}
}
