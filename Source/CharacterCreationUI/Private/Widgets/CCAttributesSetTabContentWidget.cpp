// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CCAttributesSetTabContentWidget.h"
#include "CharacterCreatorAttributesSet.h"
#include "Components/ListView.h"
#include "DataHelper/CharacterCreatorAttributeDH.h"
#include <CharacterCreator.h>

bool UCCAttributesSetTabContentWidget::Initialize()
{

	if (Super::Initialize())
	{
		return true;
	}
	return false;
}

void UCCAttributesSetTabContentWidget::SetAttributesSet(UCharacterCreatorAttributesSet* NewAttributesSet, UCharacterCreator* NewCharacterCreator)
{
	AttributesSet = NewAttributesSet;
	CharacterCreator = NewCharacterCreator;

	DataHolderArray.Empty();

	if (AttributesSet && AttributeListView && CharacterCreator)
	{
		for (UCharacterCreatorAttribute* CCAttribute : AttributesSet->Attributes)
		{
			UCharacterCreatorAttributeDH* DataHolder = NewObject<UCharacterCreatorAttributeDH>(this);
			DataHolder->CharacterCreator = CharacterCreator;
			DataHolder->CharacterCreatorAttribute = CCAttribute;
			DataHolder->Value = CharacterCreator->ValueOf(CCAttribute);
			DataHolderArray.Add(DataHolder);
		}

		AttributeListView->SetListItems(DataHolderArray);
	}
}
