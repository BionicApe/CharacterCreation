// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreatorAttributesSetTypeActions.h"
#include "CharacterCreatorAttributesSet.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorAttributesSet_TypeActions"

FCharacterCreatorAttributesSetTypeActions::FCharacterCreatorAttributesSetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorAttributesSetTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorAttributesSetTypeActionsName", "Attribute Set");
}

FColor FCharacterCreatorAttributesSetTypeActions::GetTypeColor() const
{
	return FColor::Emerald;
}

UClass* FCharacterCreatorAttributesSetTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorAttributesSet::StaticClass();
}

uint32 FCharacterCreatorAttributesSetTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE