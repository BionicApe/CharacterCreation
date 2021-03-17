// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CharacterCreatorWidget.h"
#include "CharacterCreatorAttributesSet.h"
#include "CharacterCreator.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Widgets/CCAttributesSetTabWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/CCAttributesSetTabContentWidget.h"
#include <Widgets/CCOutfitWidget.h>
#include <CharacterCreatorOutfitsSet.h>
#include <CharacterCreatorModel.h>


bool UCharacterCreatorWidget::Initialize()
{
	if (Super::Initialize())
	{
		ReloadFromCharacterCreator();
		return true;
	}
	return false;
}

void UCharacterCreatorWidget::SetCharacterCreator(UCharacterCreator* NewCharacterCreator)
{
	CharacterCreator = NewCharacterCreator;
	ReloadFromCharacterCreator();
}

void UCharacterCreatorWidget::ReloadFromCharacterCreator()
{
	if (CharacterCreatorModel && CharacterCreator && TabContentWidgetClass && TabButtonsWidgetClass && OutfitWidgetClass)
	{
		for (UCharacterCreatorAttributesSet* AttributesSet : CharacterCreatorModel->AttributesSets)
		{
			//Create the content
			if (UCCAttributesSetTabContentWidget* TabContentWidget = CreateWidget<UCCAttributesSetTabContentWidget>(GetWorld(), TabContentWidgetClass))
			{

				TabContentWidget->SetAttributesSet(AttributesSet, CharacterCreator);

				//Add Content to the Switcher
				UPanelSlot* SwitcherSlot = AttributesSetSwitcher->AddChild(TabContentWidget);

				//Create Button for the tab
				if (UCCAttributesSetTabWidget* TabWidget = CreateWidget<UCCAttributesSetTabWidget>(GetWorld(), TabButtonsWidgetClass))
				{
					CreateTab(FText::FromString(AttributesSet->AttributesSetName), TabWidget, TabContentWidget);
				}
			}
		}

		//Create the content for the Outfits
		if (UCCOutfitWidget* TabContentWidget = CreateWidget<UCCOutfitWidget>(GetWorld(), OutfitWidgetClass))
		{

			TabContentWidget->SetOutfits(CharacterCreatorModel->OutfitSets, CharacterCreator);

			//Add Content to the Switcher
			UPanelSlot* SwitcherSlot = AttributesSetSwitcher->AddChild(TabContentWidget);

			//Create Button for the tab
			if (UCCAttributesSetTabWidget* TabWidget = CreateWidget<UCCAttributesSetTabWidget>(GetWorld(), TabButtonsWidgetClass))
			{
				CreateTab(FText::FromString("Outfit"), TabWidget, TabContentWidget);
			}
		}
	}
}




void UCharacterCreatorWidget::OnTabSelected(UCCAttributesSetTabWidget* SelectedTabWidget, UWidget* SelectedContentWidget)
{

	AttributesSetSwitcher->SetActiveWidget(SelectedContentWidget);

	TArray<UWidget*> ChildrenWidgets = AttributesTabs->GetAllChildren();
	for (UWidget* ChildWidget : ChildrenWidgets)
	{
		if (UCCAttributesSetTabWidget* TabWidget = Cast<UCCAttributesSetTabWidget>(ChildWidget))
		{
			if (TabWidget == SelectedTabWidget)
			{
				TabWidget->SetStyleSelected();
			}
			else
			{
				TabWidget->SetStyleNotSelected();
			}
		}
	}
}

void UCharacterCreatorWidget::CreateTab(FText TabText, UCCAttributesSetTabWidget* SelectedTabWidget, UWidget* SelectedContentWidget)
{
	//Create Button for the tab
	if (UCCAttributesSetTabWidget* TabWidget = CreateWidget<UCCAttributesSetTabWidget>(GetWorld(), TabButtonsWidgetClass))
	{
		TabWidget->SetTabText(TabText);

		TabWidget->OnChanged().AddLambda([this, SelectedTabWidget, SelectedContentWidget]()
			{
				OnTabSelected(SelectedTabWidget, SelectedContentWidget);
			});

		//Add Tab Button to the horizontal box
		UHorizontalBoxSlot* HorizontalBoxSlot = AttributesTabs->AddChildToHorizontalBox(TabWidget);
	}
}
