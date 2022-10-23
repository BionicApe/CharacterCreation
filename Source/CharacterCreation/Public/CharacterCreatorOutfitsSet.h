// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorOutfitsSet.generated.h"

class UCharacterCreatorOutfit;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorOutfitsSet : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	FString OutfitsSetName;

	UPROPERTY(EditInstanceOnly)
	FName FriendlyName;

	UPROPERTY(EditInstanceOnly)
	TArray<UCharacterCreatorOutfit*> Outfits;

public:

	UCharacterCreatorOutfit* GetNextOutfit(UCharacterCreatorOutfit* Outfit)
	{
		int32 Index = Outfits.IndexOfByKey(Outfit);
		if (Index != INDEX_NONE)
		{
			Index = (Index + 1) % Outfits.Num();
			return Outfits[Index];
		}
		return Outfits[0];
	}

	UCharacterCreatorOutfit* GetPrevOutfit(UCharacterCreatorOutfit* Outfit)
	{
		int32 Index = Outfits.IndexOfByKey(Outfit);
		if (Index != INDEX_NONE)
		{
			int32 const OutfitsNum = Outfits.Num();
			Index = (OutfitsNum + Index - 1) % OutfitsNum;
			return Outfits[Index];
		}
		return Outfits[0];
	}
};
