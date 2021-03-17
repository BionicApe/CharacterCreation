// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorModel.generated.h"

class UCharacterCreatorAttributesSet;
class UCharacterCreatorAttribute;
class UCharacterCreatorOutfitsSet;
class UCharacterCreatorOutfit;
class UCharacterCreatorOutfitSlot;

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreatorModel : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TArray<UCharacterCreatorAttributesSet*> AttributesSets;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TMap<UCharacterCreatorOutfitSlot*,UCharacterCreatorOutfitsSet*> OutfitSets;
//
//public:
//
//	float ValueOf(UCharacterCreatorAttribute* CCAttribute);
//
//	void SetAttributeValue(UCharacterCreatorAttribute* Attribute, float NewValue);
//
//	int32 GetSelectedOutfitIndex(UCharacterCreatorOutfitsSet* CCOutfitSet);
//
//	UCharacterCreatorOutfit* GetSelectedOutfit(UCharacterCreatorOutfitsSet* CCOutfitSet);
//
//	void SetOutfit(UCharacterCreatorOutfitsSet* CCOutfitSet, int32 Index);
};
