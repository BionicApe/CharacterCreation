// Created by Bionic Ape. All Rights Reserved.


#include "Components/CharacterCreatorControlComponent.h"
#include "CharacterCreator.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/CharacterCreationSubsystem.h"
#include "Interfaces/CharacterCreationDAO.h"


void UCharacterCreatorControlComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreatorControlComponent, CharacterCreators);
}

bool UCharacterCreatorControlComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	WroteSomething |= Channel->ReplicateSubobjectList(CharacterCreators, *Bunch, *RepFlags);
	return WroteSomething;
}

void UCharacterCreatorControlComponent::AddCharacterCreator(UCharacterCreator* NewCharacterCreator)
{
	CharacterCreators.AddUnique(NewCharacterCreator);
}


void UCharacterCreatorControlComponent::SetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	Server_SetAttributeValue(NewCharacterCreator, CCAttribute, NewValue);
}

void UCharacterCreatorControlComponent::Server_SetAttributeValue_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetAttributeValue(CCAttribute, NewValue);
	}
}

void UCharacterCreatorControlComponent::SetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit)
{
	Server_SetOutfit(CharacterCreator, SelectedOutfit);
}

void UCharacterCreatorControlComponent::Server_SetOutfit_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetOutfit(SelectedOutfit);
	}
}

void UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation(UCharacterCreator* CharacterCreator)
{
	if (!CharacterCreator)
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation() CharacterCrator is null"));
		return;
	}
	if (!CharacterCreators.Contains(CharacterCreator))
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation() CharacterCreator not found in CharacterCreators"));
		return;
	}
	
	if (!GetWorld() || !GetWorld()->GetGameInstance())
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation() World is null or GameInstance is null"));
		return;
	}

	UCharacterCreationSubsystem const* const CCSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCharacterCreationSubsystem>();
	if (ICharacterCreationDAO* const DAO = CCSubsystem->GetDao())
	{
		FAsyncSaveCharacterCreatorDelegate Delegate;
		DAO->SaveCharacterCreator(CharacterCreator, Delegate);
	}
}
