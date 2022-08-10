// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorOutfitDH.generated.h"

class UCharacterCreatorOutfit;
class UCharacterCreatorOutfitsSet;
class UCharacterCreatorOutfitSlot;
class UCharacterCreator;

/**
 *
 */
UCLASS()
class CHARACTERCREATIONUI_API UCharacterCreatorOutfitDH : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UCharacterCreatorOutfitsSet* OutfitsSet;

	UPROPERTY(EditAnywhere)
	UCharacterCreatorOutfitSlot* OutfitSlot;

	UPROPERTY(EditAnywhere)
	UCharacterCreatorOutfit* SelectedOutfit;

	UPROPERTY(EditAnywhere)
	UCharacterCreator* CharacterCreator;
};
