// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorGroomDH.generated.h"

class UCharacterCreatorGroom;
class UCharacterCreatorGroomsSet;
class UCharacterCreator;
class UCharacterCreatorOutfitSlot;

/**
 *
 */
UCLASS()
class CHARACTERCREATIONUI_API UCharacterCreatorGroomDH : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UCharacterCreatorGroomsSet* GroomsSet;

	UPROPERTY(EditAnywhere)
	UCharacterCreatorOutfitSlot* GroomSlot;

	UPROPERTY(EditAnywhere)
	UCharacterCreatorGroom* SelectedGroom;

	UPROPERTY(EditAnywhere)
	UCharacterCreator* CharacterCreator;
};
