// Created by Bionic Ape. All rights reseved.


#include "CharacterCreatorModel.h"

bool UCharacterCreatorModel::ContainsSlot(const UCharacterCreatorOutfitSlot* FindSlot)
{
	if (Slots.IsEmpty()) {
		return false;
	}
	return Slots.Contains(FindSlot);
}

bool UCharacterCreatorModel::ContainsSlot(const FString& SlotID)
{
	//TODO think of something better
	for (UCharacterCreatorOutfitSlot* Slot : Slots)
	{
		if (Slot->Name == SlotID)
		{
			return true;
		}
	}
	return false;
}

UCharacterCreatorOutfitSlot* UCharacterCreatorModel::GetSlot(const FString& SlotID)
{
	//TODO think of something better
	for (UCharacterCreatorOutfitSlot* Slot : Slots)
	{
		if (Slot->Name == SlotID)
		{
			return Slot;
		}
	}
	return nullptr;
}
