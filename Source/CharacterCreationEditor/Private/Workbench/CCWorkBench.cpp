// Created by Bionic Ape. All Rights Reserved.

#include "Workbench/CCWorkbench.h"
//#include "Workbench/CCWorkbenchCommands.h"
#include "Workbench/SCCWorkbench.h"

#include "CharacterCreationStyle.h"

#include "Framework/Docking/TabManager.h"
#include "Framework/Commands/UICommandList.h"

#include "ToolMenus.h"
#include "ToolMenu.h"
#include "ToolMenuEntry.h"

#include "Framework/Commands/UIAction.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"


#define LOCTEXT_NAMESPACE "MainMenuSystem"

namespace
{
	const FName CCWorkbenchWindowID = FName(TEXT("CCWorkbench"));

	TSharedRef<class SDockTab> SpawnNomadTab(const FSpawnTabArgs& Args)
	{
		return SNew(SDockTab)
			.TabRole(NomadTab)
			[
				SNew(SCCWorkbench)
			];
	}
}

void FCCWorkbench::Register()
{
	//FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
	//	CCWorkbenchWindowID,
	//	FOnSpawnTab::CreateStatic(&SpawnNomadTab))
	//		.SetDisplayName(LOCTEXT("TabTitle", "Character Creator Workbench"))
	//		.SetTooltipText(LOCTEXT("TooltipText", "Access all Bionic Character Creator Workbench Tools"))
	//		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
	//		.SetIcon(FSlateIcon(FCharacterCreationStyle::GetStyleSetName(),
	//	"CharacterCreationEditor.Image")
	//);

	//UToolMenu* AssetsToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AssetsToolBar");
	//if (AssetsToolBar)
	//{
	//	FToolMenuSection& Section = AssetsToolBar->AddSection("Content");
	//	FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(
	//		"CharacterCreationEditorLaunchPad",
	//		FUIAction(FExecuteAction::CreateStatic(&FCCWorkbench::Launch)),
	//		LOCTEXT("CCWorkbench_Friendly", "Character Creator Workbench"),
	//		LOCTEXT("CCWorkbench_Tooltip", "Character Creator Workbench Tools"),
	//		FSlateIcon(FCharacterCreationStyle::GetStyleSetName(), TEXT("CharacterCreationEditor.Image")));
	//	ToolMenuEntry.StyleNameOverride = "CalloutToolbar";
	//	Section.AddEntry(ToolMenuEntry);
	//}
}

void FCCWorkbench::Unregister()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CCWorkbenchWindowID);
}

void FCCWorkbench::Launch()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CCWorkbenchWindowID);
}

#undef LOCTEXT_NAMESPACE
