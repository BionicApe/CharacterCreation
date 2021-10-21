// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreationCommands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FCharacterCreationModule"

void FCharacterCreationCommands::RegisterCommands()
{
	UI_COMMAND(OpenCharacterCreationEditorAction, "Character Creation Editor", "Opens Character Creation Editor", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
