// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorOutfitDH.generated.h"

class UCharacterCreatorOutfit;
class UCharacterCreatorOutfitsSet;
class UCharacterCreator;
class UCharacterCreatorOutfitSlot;

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
