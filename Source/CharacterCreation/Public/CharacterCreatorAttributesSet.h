// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorAttributesSet.generated.h"

class UCharacterCreatorAttribute;

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreatorAttributesSet : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	FString AttributesSetName;

	UPROPERTY(EditInstanceOnly)
 	TArray<UCharacterCreatorAttribute*> Attributes;
};
