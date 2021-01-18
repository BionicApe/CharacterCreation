// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreationEditor.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "CharacterCreatorTypeActions.h"

#define LOCTEXT_NAMESPACE "FCharacterCreationEditorModule"

void FCharacterCreationEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Assets Category
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CharacterCreationEditor")), LOCTEXT("CharacterCreationEditor", "Character Creation"));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorTypeActions(AssetCategoryBit)));
}

void FCharacterCreationEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCharacterCreationEditorModule, CharacterCreationEditor)