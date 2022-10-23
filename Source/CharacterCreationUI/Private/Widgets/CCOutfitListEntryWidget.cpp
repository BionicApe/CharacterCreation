// Created by Bionic Ape. All rights reseved.


#include "Widgets/CCOutfitListEntryWidget.h"
#include "CharacterCreatorOutfit.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "DataHelper/CharacterCreatorOutfitDH.h"
#include "Components/Button.h"
#include "CharacterCreator.h"
#include "CharacterCreatorOutfitsSet.h"
#include "Components/CharacterCreatorControlComponent.h"

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
	SetOutfit(true/*Left*/);
}

void UCCOutfitListEntryWidget::OnRightClicked()
{
	SetOutfit(false/*Right*/);
}


void UCCOutfitListEntryWidget::SetOutfit(bool bDirectionIsLeft)
{
	if (!CCOutfitDH || !CCOutfitDH->OutfitsSet || !CCOutfitDH->CharacterCreator)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::OnValueChanged() Bad values !CCOutfitDH || !CCOutfitDH->OutfitsSet || !CCOutfitDH->CharacterCreator"));
		return;
	}

	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::OnValueChanged() No Owning PlayerController Found"));
		return;
	}

	UCharacterCreatorControlComponent* CCControlComp = Cast<UCharacterCreatorControlComponent>(PC->GetComponentByClass(UCharacterCreatorControlComponent::StaticClass()));
	if (!CCControlComp)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCOutfitListEntryWidget::OnValueChanged() No UCharacterCreatorControlComponent Found"));
		return;
	}

	CCOutfitDH->SelectedOutfit = bDirectionIsLeft ? CCOutfitDH->OutfitsSet->GetPrevOutfit(CCOutfitDH->SelectedOutfit) : CCOutfitDH->OutfitsSet->GetNextOutfit(CCOutfitDH->SelectedOutfit);
	CCControlComp->SetOutfit(CCOutfitDH->CharacterCreator, CCOutfitDH->SelectedOutfit);
	UpdateOutfitText();
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
		NameTextWidget->SetText(FText::FromName(CCOutfitDH->OutfitsSet->FriendlyName));
	}
}

void UCCOutfitListEntryWidget::UpdateOutfitText()
{
	if (SelectedOutfitName && CCOutfitDH->SelectedOutfit)
	{
		SelectedOutfitName->SetText(FText::FromName(CCOutfitDH->SelectedOutfit->FriendlyName));
	}
}