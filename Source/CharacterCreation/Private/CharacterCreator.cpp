// Created by Bionic Ape. All Rights Reserved.


#include "CharacterCreator.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorOutfitsSet.h"
#include "CharacterCreatorAttributesSet.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorOutfitSlot.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


float UCharacterCreator::ValueOf(UCharacterCreatorAttribute* CCAttribute)
{
	for (FCCAttributeValue AttributeValue : AttributeValues)
	{
		if (AttributeValue.Attribute == CCAttribute)
		{
			return AttributeValue.Value;
		}
	}
	return 0.f;
}

void UCharacterCreator::SetAttributeValue(UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	ServerSetAttributeValue(CCAttribute, NewValue);
}

void UCharacterCreator::ServerSetAttributeValue_Implementation(UCharacterCreatorAttribute* Attribute, float NewValue)
{
	for (FCCAttributeValue& AttributeValue : AttributeValues)
	{
		if (AttributeValue.Attribute == Attribute)
		{
			AttributeValue.Value = NewValue;
			break;
		}
	}
	AttributeValues.Emplace(Attribute, NewValue);//We create a new entry otherwise
	MulticastOnChanged();
}

void UCharacterCreator::MulticastOnChanged_Implementation()
{
	OnChanged.Broadcast();
}

UCharacterCreatorOutfit* UCharacterCreator::GetSelectedOutfit(UCharacterCreatorOutfitSlot* Slot)
{
	for (FCCSlotAndOutfit& SlotAndOutfit : SlotAndOutfitArray)
	{
		if (SlotAndOutfit.Slot == Slot)
		{
			return SlotAndOutfit.Outfit;
		}
	}
	return nullptr;
}

void UCharacterCreator::SetOutfit(UCharacterCreatorOutfit* Outfit)
{
	ServerSetOutfit_Implementation(Outfit);
}

void UCharacterCreator::ServerSetOutfit_Implementation(UCharacterCreatorOutfit* Outfit)
{
	if (Outfit && Outfit->Slot)
	{
		for (FCCSlotAndOutfit& SlotAndOutfit : SlotAndOutfitArray)
		{
			if (SlotAndOutfit.Slot == Outfit->Slot)
			{
				SlotAndOutfit.Outfit = Outfit;
				break;
			}
		}
	}
	MulticastOnChanged();
}

void UCharacterCreator::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreator, SlotAndOutfitArray);
	DOREPLIFETIME(UCharacterCreator, AttributeValues);
	DOREPLIFETIME(UCharacterCreator, OnChanged);
}