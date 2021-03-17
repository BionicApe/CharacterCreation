// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CCAttributeListEntryWidget.h"
#include "CharacterCreatorAttribute.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "Components/Slider.h"
#include "DataHelper/CharacterCreatorAttributeDH.h"
#include "CharacterCreator.h"

bool UCCAttributeListEntryWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (MorphSlider)
		{
			MorphSlider->OnValueChanged.AddDynamic(this, &UCCAttributeListEntryWidget::OnValueChanged);
			return true;
		}
	}
	return false;
}

void UCCAttributeListEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	CCAttributeDH = Cast<UCharacterCreatorAttributeDH>(ListItemObject);

	if (!CCAttributeDH && CCAttributeDH->CharacterCreatorAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCAttributeListEntryWidget::NativeOnListItemObjectSet() ListItemObject empty or not of class UCharacterCreatorAttribute"));
		return;
	}

	NameTextWidget->SetText(FText::FromName(CCAttributeDH->CharacterCreatorAttribute->FriendlyName));
	MorphMinTextWidget->SetText(FText::FromString(FString::SanitizeFloat(CCAttributeDH->CharacterCreatorAttribute->MorphMin)));
	MorphMaxTextWidget->SetText(FText::FromString(FString::SanitizeFloat(CCAttributeDH->CharacterCreatorAttribute->MorphMax)));
	MorphSlider->SetValue(CCAttributeDH->Value);
	MorphSlider->SetMaxValue(CCAttributeDH->CharacterCreatorAttribute->MorphMax);
	MorphSlider->SetMinValue(CCAttributeDH->CharacterCreatorAttribute->MorphMin);
}

void UCCAttributeListEntryWidget::OnValueChanged(float NewValue)
{
	if (!CCAttributeDH)
	{
		UE_LOG(LogTemp, Error, TEXT("UCCAttributeListEntryWidget::OnValueChanged() CCAttribute empty"));
		return;
	}

	CCAttributeDH->CharacterCreator->SetAttributeValue(CCAttributeDH->CharacterCreatorAttribute, NewValue);
}
