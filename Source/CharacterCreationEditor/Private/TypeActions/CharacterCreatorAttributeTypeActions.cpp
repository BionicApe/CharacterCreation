// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/CharacterCreatorAttributeTypeActions.h"
#include "CharacterCreatorAttribute.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorAttribute_TypeActions"

FCharacterCreatorAttributeTypeActions::FCharacterCreatorAttributeTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorAttributeTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorAttributeTypeActionsName", "Attribute");
}

FColor FCharacterCreatorAttributeTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FCharacterCreatorAttributeTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorAttribute::StaticClass();
}

uint32 FCharacterCreatorAttributeTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE