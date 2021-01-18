// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreatorTypeActions.h"
#include "CharacterCreator.h"

#define LOCTEXT_NAMESPACE "CharacterCreator_TypeActions"

FCharacterCreatorTypeActions::FCharacterCreatorTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorTypeActionsName", "Character Creator");
}

FColor FCharacterCreatorTypeActions::GetTypeColor() const
{
	return FColor::Blue;
}

UClass* FCharacterCreatorTypeActions::GetSupportedClass() const
{
	return UCharacterCreator::StaticClass();
}

uint32 FCharacterCreatorTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE