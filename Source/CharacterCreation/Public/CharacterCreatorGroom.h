// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorGroom.generated.h"

class UGroomAsset;
class UCharacterCreatorOutfitSlot;
class UGroomBindingAsset;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorGroom : public UObject
{
	GENERATED_BODY()

public:


	UPROPERTY(EditInstanceOnly)
	FName OutfitName;

	UPROPERTY(EditInstanceOnly)
	FName FriendlyName;

	UPROPERTY(EditInstanceOnly)
	UCharacterCreatorOutfitSlot* Slot;

	UPROPERTY(EditInstanceOnly)
	UCharacterCreatorOutfitSlot* SlotToAttach;

	UPROPERTY(EditInstanceOnly)
	UGroomBindingAsset* Binding;

	UPROPERTY(EditInstanceOnly)
	UGroomAsset* GroomAsset;

	UPROPERTY(EditInstanceOnly)
	int32 DatabaseId;
};
