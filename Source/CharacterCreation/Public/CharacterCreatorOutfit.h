// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorOutfit.generated.h"

class USkeletalMesh;
class UCharacterCreatorOutfitSlot;

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreatorOutfit : public UObject
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
	USkeletalMesh* Mesh;

	UPROPERTY(EditInstanceOnly)
	int32 DatabaseId;
};
