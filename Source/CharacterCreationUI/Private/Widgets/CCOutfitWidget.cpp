// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CCOutfitWidget.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreator.h"
#include "CharacterCreatorOutfitsSet.h"
#include "DataHelper/CharacterCreatorOutfitDH.h"
#include "Components/ListView.h"
#include <CharacterCreationTypes.h>

bool UCCOutfitWidget::Initialize()
{

	if (Super::Initialize())
	{
		return true;
	}
	return false;
}

void UCCOutfitWidget::SetOutfits(TMap<UCharacterCreatorOutfitSlot*, UCharacterCreatorOutfitsSet*> NewOutfitsSetMap, UCharacterCreator* NewCharacterCreator)
{

	OutfitsSetMap = NewOutfitsSetMap;
	CharacterCreator = NewCharacterCreator;

	DataHolderArray.Empty();

	if (OutfitListView && CharacterCreator)
	{

		for (const TPair<UCharacterCreatorOutfitSlot*, UCharacterCreatorOutfitsSet*>& pair : OutfitsSetMap)
		{
			pair.Key;
			pair.Value;

			UCharacterCreatorOutfitDH* DataHolder = NewObject<UCharacterCreatorOutfitDH>(this);
			DataHolder->CharacterCreator = CharacterCreator;
			DataHolder->OutfitsSet = pair.Value;
			DataHolder->OutfitSlot = pair.Key;
			DataHolder->SelectedOutfit = CharacterCreator->CharacterCreation.GetOutfitForSlot(pair.Key);
			DataHolderArray.Add(DataHolder);
		}

		OutfitListView->SetListItems(DataHolderArray);
	}
}
