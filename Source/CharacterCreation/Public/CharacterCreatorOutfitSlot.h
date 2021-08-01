// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorOutfitSlot.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreatorOutfitSlot : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	FString Name;
	
	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	FName FriendlyName;

	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	FString DatabaseColumnName;
	
	UPROPERTY(EditAnywhere, Category = "CharacterCreation")
	bool bIsRoot = false;
};
