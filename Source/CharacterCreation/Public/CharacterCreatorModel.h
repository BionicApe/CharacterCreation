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

	
	//TODO: I think it can be devided these 3 properties to another class, they are only used by the database
	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	int32 DatabaseIdColumn;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TArray<UCharacterCreatorOutfitSlot*> Slots;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TMap<int32, UCharacterCreatorOutfit*> Outfits;

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
