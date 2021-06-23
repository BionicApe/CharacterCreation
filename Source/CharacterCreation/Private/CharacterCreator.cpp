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


void UCharacterCreator::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreator, SlotAndOutfitArray);
	DOREPLIFETIME(UCharacterCreator, AttributeValues);
}

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
	bool bIsFound = false;
	for (FCCAttributeValue& AttributeValue : AttributeValues)
	{
		if (AttributeValue.Attribute == CCAttribute)
		{
			AttributeValue.Value = NewValue;
			bIsFound = true;
			break;
		}
	}
	if (!bIsFound)
	{
		AttributeValues.Emplace(CCAttribute, NewValue);//We create a new entry otherwise
	}
	//OnChanged.Broadcast();
	OnAttributeChangedDelegate.Broadcast(CCAttribute, NewValue);
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
	bool bIsFound = false;
	if (Outfit && Outfit->Slot)
	{
		for (FCCSlotAndOutfit& SlotAndOutfit : SlotAndOutfitArray)
		{
			if (SlotAndOutfit.Slot == Outfit->Slot)
			{
				SlotAndOutfit.Outfit = Outfit;
				bIsFound = true;
				break;
			}
		}
	}
	if (!bIsFound)
	{
		SlotAndOutfitArray.Emplace(Outfit->Slot, Outfit);//We create a new entry otherwise
	}
	OnOutfitChangedDelegate.Broadcast(Outfit);
	//OnChanged.Broadcast();
}