// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorAttributeDH.generated.h"

class UCharacterCreatorAttribute;

/**
 *
 */
UCLASS()
class CHARACTERCREATIONUI_API UCharacterCreatorAttributeDH : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float Value = 0.f;	
	
	UPROPERTY(EditAnywhere)
	UCharacterCreatorAttribute* CharacterCreatorAttribute;	

	UPROPERTY(EditAnywhere)
	UCharacterCreator* CharacterCreator;
};
