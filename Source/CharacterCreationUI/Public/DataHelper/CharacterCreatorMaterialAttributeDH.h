// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorMaterialAttributeDH.generated.h"

class UCharacterCreatorMatAttribute;

/**
 *
 */
UCLASS()
class CHARACTERCREATIONUI_API UCharacterCreatorMaterialAttributeDH : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float Value = 0.f;	

	UPROPERTY(EditAnywhere)
	UCharacterCreatorMatAttribute* CharacterCreatorMaterialAttribute;

	UPROPERTY(EditAnywhere)
	UCharacterCreator* CharacterCreator;
};
