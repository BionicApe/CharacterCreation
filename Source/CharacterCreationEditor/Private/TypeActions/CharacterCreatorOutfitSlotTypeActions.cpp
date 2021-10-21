// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/CharacterCreatorOutfitSlotTypeActions.h"
#include "CharacterCreatorOutfitSlot.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorOutfitSlot_TypeActions"

FCharacterCreatorOutfitSlotTypeActions::FCharacterCreatorOutfitSlotTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorOutfitSlotTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorOutfitSlotTypeActionsName", "Outfit Slot");
}

FColor FCharacterCreatorOutfitSlotTypeActions::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FCharacterCreatorOutfitSlotTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorOutfitSlot::StaticClass();
}

uint32 FCharacterCreatorOutfitSlotTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE