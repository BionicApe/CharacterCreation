// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/CharacterCreatorOutfitsSetTypeActions.h"
#include "CharacterCreatorOutfitsSet.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorOutfitsSet_TypeActions"

FCharacterCreatorOutfitsSetTypeActions::FCharacterCreatorOutfitsSetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorOutfitsSetTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorOutfitsSetTypeActionsName", "Outfit Set");
}

FColor FCharacterCreatorOutfitsSetTypeActions::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FCharacterCreatorOutfitsSetTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorOutfitsSet::StaticClass();
}

uint32 FCharacterCreatorOutfitsSetTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE