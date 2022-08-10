// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/CharacterCreatorMatAttributeTypeActions.h"
#include "CharacterCreatorMatAttribute.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorMatAttribute_TypeActions"

FCharacterCreatorMatAttributeTypeActions::FCharacterCreatorMatAttributeTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorMatAttributeTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorMatAttributeTypeActionsName", "Material Attribute");
}

FColor FCharacterCreatorMatAttributeTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FCharacterCreatorMatAttributeTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorMatAttribute::StaticClass();
}

uint32 FCharacterCreatorMatAttributeTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE