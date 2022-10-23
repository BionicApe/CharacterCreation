// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorAttributesSet.generated.h"

class UCharacterCreatorAttribute;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorAttributesSet : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	FString AttributesSetName;

	UPROPERTY(EditInstanceOnly)
 	TArray<UCharacterCreatorAttribute*> Attributes;
};
