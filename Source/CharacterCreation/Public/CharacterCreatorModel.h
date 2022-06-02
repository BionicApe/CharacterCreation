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
	TMap<FString, UCharacterCreatorAttribute*> Attributes;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TMap<UCharacterCreatorOutfitSlot*,UCharacterCreatorOutfitsSet*> OutfitSets;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	TArray<UCharacterCreatorOutfitSlot*> Slots;

	bool ContainsSlot(const FString& SlotID);

	UCharacterCreatorOutfitSlot* GetSlot(const FString& SlotID);

	//UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	//TMap<FString, UCharacterCreatorOutfitSlot*> SlotsMap;

	//UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	//TMap<FString, UCharacterCreatorOutfit*> OutfitsMap;

	//UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	//TMap<int32, UCharacterCreatorOutfit*> Outfits;
};