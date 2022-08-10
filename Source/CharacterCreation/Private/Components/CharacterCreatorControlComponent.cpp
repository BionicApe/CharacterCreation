// Created by Bionic Ape. All Rights Reserved.


#include "Components/CharacterCreatorControlComponent.h"
#include "CharacterCreator.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/CharacterCreationSubsystem.h"
#include "Interfaces/CharacterCreationDAO.h"

////This adds a dependency which might not be necessary, and it is causing a build error
//#include "DataHelper/CharacterCreatorSlotDH.h"


void UCharacterCreatorControlComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreatorControlComponent, CharacterCreators);
	DOREPLIFETIME(UCharacterCreatorControlComponent, MainCharacterCreator);
}

bool UCharacterCreatorControlComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	WroteSomething |= Channel->ReplicateSubobjectList(CharacterCreators, *Bunch, *RepFlags);
	return WroteSomething;
}

void UCharacterCreatorControlComponent::AddCharacterCreator(UCharacterCreator* NewCharacterCreator, bool bIsMainCC /*= true*/)
{
	CharacterCreators.AddUnique(NewCharacterCreator);
	if (bIsMainCC)
	{
		MainCharacterCreator = NewCharacterCreator;
	}
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

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
void UCharacterCreatorControlComponent::SetMaterialAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, float NewValue)
{
	Server_SetMaterialAttributeValue(NewCharacterCreator, CCAttribute, NewValue);
}

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
void UCharacterCreatorControlComponent::Server_SetMaterialAttributeValue_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, float NewValue)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetMaterialAttributeValue(CCAttribute, NewValue);
	}
}

void UCharacterCreatorControlComponent::SetMaterialAttributeAffectedSlots(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool NewValue)
{
	Server_SetMaterialAttributeAffectedSlots(NewCharacterCreator, CCAttribute, Slot, NewValue);
}

//void UCharacterCreatorControlComponent::SetMaterialAttributeAffectedSlots(UCharacterCreatorSlotDH* CCSlotDH, bool NewValue)
//{
//	OnCCMatAttAffectedSlotsChanged.Broadcast(CCSlotDH, NewValue);
//	Server_SetMaterialAttributeAffectedSlots(CCSlotDH->CharacterCreator, CCSlotDH->MaterialAttribute, CCSlotDH->OutfitSlot, NewValue);
//}

void UCharacterCreatorControlComponent::Server_SetMaterialAttributeAffectedSlots_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool NewValue)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetMaterialAttributeAffectedSlots(CCAttribute, Slot, NewValue);
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

void UCharacterCreatorControlComponent::SetGroom(UCharacterCreator* CharacterCreator, UCharacterCreatorGroom* SelectedGroom)
{
	Server_SetGroom(CharacterCreator, SelectedGroom);
}

void UCharacterCreatorControlComponent::Server_SetGroom_Implementation(UCharacterCreator* CharacterCreator, UCharacterCreatorGroom* SelectedGroom)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetGroom(SelectedGroom);
	}
}

void UCharacterCreatorControlComponent::SetBodyType(UCharacterCreator* CharacterCreator, FCharacterCreationBodyType NewBodyType)
{
	Server_SetBodyType(CharacterCreator, NewBodyType);
}

void UCharacterCreatorControlComponent::Server_SetBodyType_Implementation(UCharacterCreator* CharacterCreator, FCharacterCreationBodyType NewBodyType)
{
	if (CharacterCreator && CharacterCreators.Contains(CharacterCreator))
	{
		CharacterCreator->SetBodyType(NewBodyType);
	}
}

void UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation(UCharacterCreator* CharacterCreator)
{
	if (!CharacterCreator)
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation() CharacterCreator is null"));
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

	const ICharacterCreationDAOOwner* const DaoOwner = Cast<ICharacterCreationDAOOwner>(GetWorld()->GetGameInstance());
	if (!DaoOwner)
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorControlComponent::Server_SaveCharacterCreator_Implementation() GameInstance is not ICharacterCreationDAOOwner"));
		return;
	}

	ICharacterCreationDAO* Dao = DaoOwner->GetCharacterCreationDAO();
	if (Dao)
	{
		FAsyncSaveCharacterCreatorDelegate Delegate;
		//Delegate.BindUObject(this, &UCharacterCreatorControlComponent::OnDaoResponse);
		Dao->SaveCharacterCreator(CharacterCreator, Delegate);
	}
}

void UCharacterCreatorControlComponent::OnDaoResponse(FAsyncCharacterCreatorResponse Response)
{
	Client_Notify(Response.bIsSuccessful, Response.ErrorMessage);
}
