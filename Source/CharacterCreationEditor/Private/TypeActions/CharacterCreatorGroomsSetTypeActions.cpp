// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/CharacterCreatorGroomsSetTypeActions.h"
#include "CharacterCreatorGroomsSet.h"

#define LOCTEXT_NAMESPACE "CharacterCreatorGroomsSet_TypeActions"

FCharacterCreatorGroomsSetTypeActions::FCharacterCreatorGroomsSetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FCharacterCreatorGroomsSetTypeActions::GetName() const
{
	return LOCTEXT("FCharacterCreatorGroomsSetTypeActionsName", "Groom Set");
}

FColor FCharacterCreatorGroomsSetTypeActions::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FCharacterCreatorGroomsSetTypeActions::GetSupportedClass() const
{
	return UCharacterCreatorGroomsSet::StaticClass();
}

uint32 FCharacterCreatorGroomsSetTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE