// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreationEditor.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"

#include "TypeActions/CharacterCreatorTypeActions.h"
#include "TypeActions/CharacterCreatorAttributeTypeActions.h"
#include "TypeActions/CharacterCreatorAttributesSetTypeActions.h"
#include "TypeActions/CharacterCreatorOutfitsSetTypeActions.h"
#include "TypeActions/CharacterCreatorOutfitTypeActions.h"
#include "TypeActions/CharacterCreatorOutfitSlotTypeActions.h"
#include "TypeActions/CharacterCreatorModelTypeActions.h"

#include "Framework/Commands/UICommandList.h"
#include "CharacterCreationStyle.h"
#include "CharacterCreationCommands.h"
#include "Classes/EditorStyleSettings.h"
#include "LevelEditor.h"
#include "Private/Workbench/CCWorkBench.h"

#include "Workbench/SCCWorkbench.h"
#include "DetailCustomization/BASkeletalMeshDetailCustomization.h"

#define LOCTEXT_NAMESPACE "FCharacterCreationEditorModule"

void FCharacterCreationEditorModule::StartupModule()
{
	//Call this to make sure AnimGraph module is setup
	FModuleManager::Get().LoadModuleChecked(TEXT("Persona"));

	//Custom Class Layout
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout(USkeletalMesh::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FBASkeletalMeshDetailCustomization::MakeInstance));

		PropertyModule.NotifyCustomizationModuleChanged();
	}

	//Style
	FCharacterCreationStyle::Initialize();
	FCharacterCreationStyle::ReloadTextures();
	//End Style


	// Assets Category
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	EAssetTypeCategories::Type AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CharacterCreationEditor")), LOCTEXT("CharacterCreationEditor", "Character Creation"));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorAttributeTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorAttributesSetTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorOutfitTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorOutfitsSetTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorOutfitSlotTypeActions(AssetCategoryBit)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FCharacterCreatorModelTypeActions(AssetCategoryBit)));

	FCharacterCreationStyle::Initialize();

	FCharacterCreationCommands::Register();
	
	FCCWorkbench::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction
	(
		FCharacterCreationCommands::Get().OpenCharacterCreationEditorAction,
		FExecuteAction::CreateStatic(&FCCWorkbench::Launch)
	);
}

void FCharacterCreationEditorModule::ShutdownModule()
{
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCharacterCreationEditorModule, CharacterCreationEditor)