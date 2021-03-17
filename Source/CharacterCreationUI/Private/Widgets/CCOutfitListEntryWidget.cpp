// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CCOutfitListEntryWidget.h"
#include "CharacterCreatorOutfit.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "DataHelper/CharacterCreatorOutfitDH.h"
#include "Components/Button.h"
#include "CharacterCreator.h"
#include <CharacterCreatorOutfitsSet.h>

bool UCCOutfitListEntryWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (LeftButton && RightButton)
		{
			LeftButton->OnClicked.AddDynamic(this, &UCCOutfitListEntryWidget::OnLeftClicked);
			RightButton->OnClicked.AddDynamic(this, &UCCOutfitListEntryWidget::OnRightClicked);
			return true;
		}
	}
	return false;
}

void UCCOutfitListEntryWidget::OnLeftClicked()
{
	if (!CCOutfitDH)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::OnValueChanged() CCOutfit empty"));
		return;
	}

	if (CCOutfitDH && CCOutfitDH->OutfitsSet && CCOutfitDH->CharacterCreator)
	{
		CCOutfitDH->SelectedOutfit = CCOutfitDH->OutfitsSet->GetPrevOutfit(CCOutfitDH->SelectedOutfit);
		CCOutfitDH->CharacterCreator->SetOutfit(CCOutfitDH->SelectedOutfit);
		UpdateOutfitText();
	}
}

void UCCOutfitListEntryWidget::OnRightClicked()
{
	if (!CCOutfitDH)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::OnValueChanged() CCOutfit empty"));
		return;
	}

	if (CCOutfitDH && CCOutfitDH->OutfitsSet && CCOutfitDH->CharacterCreator)
	{
		CCOutfitDH->SelectedOutfit = CCOutfitDH->OutfitsSet->GetNextOutfit(CCOutfitDH->SelectedOutfit);
		CCOutfitDH->CharacterCreator->SetOutfit(CCOutfitDH->SelectedOutfit);
		UpdateOutfitText();
	}
}

void UCCOutfitListEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	CCOutfitDH = Cast<UCharacterCreatorOutfitDH>(ListItemObject);

	if (!CCOutfitDH && CCOutfitDH->CharacterCreator)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::NativeOnListItemObjectSet() ListItemObject empty or not of class UCharacterCreatorOutfitDH"));
		return;
	}

	UpdateOutfitText();

	if (NameTextWidget && CCOutfitDH->OutfitsSet)
	{
		NameTextWidget->SetText(FText::FromName(CCOutfitDH->OutfitsSet->FriendlyName));;
	}
}

void UCCOutfitListEntryWidget::UpdateOutfitText()
{
	if (SelectedOutfitName && CCOutfitDH->SelectedOutfit)
	{
		SelectedOutfitName->SetText(FText::FromName(CCOutfitDH->SelectedOutfit->FriendlyName));
	}
}