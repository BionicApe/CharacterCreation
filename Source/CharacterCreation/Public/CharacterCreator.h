// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreator.generated.h"

class UCharacterCreatorAttributesSet;
class UCharacterCreatorAttribute;
class UCharacterCreatorOutfit;
class UCharacterCreatorOutfitSlot;

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreator : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	FCharacterCreation CharacterCreation;
		
public:
	
	float ValueOf(UCharacterCreatorAttribute* CCAttribute);

	void SetAttributeValue(UCharacterCreatorAttribute* Attribute, float NewValue);

	UCharacterCreatorOutfit* GetSelectedOutfit(UCharacterCreatorOutfitSlot* OutfitSlot);

	void SetOutfit(UCharacterCreatorOutfit* CCOutfit);
};
