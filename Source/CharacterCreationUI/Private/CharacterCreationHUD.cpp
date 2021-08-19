// Created by Bionic Ape. All rights reseved.


#include "CharacterCreationHUD.h"
#include "Widgets/CharacterCreatorWidget.h"

void ACharacterCreationHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterCreationHUD::CreateCCWidget(UCharacterCreator* CharacterCreator)
{
	if (CCWidget)
	{
		CCWidget->RemoveFromParent();
		CCWidget = nullptr;
	}

	if (CCWidgetClass)
	{
		CCWidget = CreateWidget<UCharacterCreatorWidget>(GetOwningPlayerController(), CCWidgetClass);
		CCWidget->SetNewCharacterCreator(CharacterCreator);
		CCWidget->AddToViewport();
	}
}
