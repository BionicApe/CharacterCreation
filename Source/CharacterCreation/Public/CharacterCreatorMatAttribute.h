// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorMatAttribute.generated.h"

/**
 * 
 */

class UCharacterCreatorOutfitSlot;

UCLASS()
class CHARACTERCREATION_API UCharacterCreatorMatAttribute : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly)
	FName ScalarParameterName;

	UPROPERTY(EditInstanceOnly)
	FName FriendlyName;

	UPROPERTY(EditInstanceOnly)
	float ValueMin = -1.f;

	UPROPERTY(EditInstanceOnly)
	float ValueMax = 1.f;

	UPROPERTY(EditInstanceOnly)
	FString DatabaseColumnName;

	UPROPERTY(EditInstanceOnly)
	TArray<UCharacterCreatorOutfitSlot*> PermitedSlots;

	UPROPERTY(EditInstanceOnly)
	UCharacterCreatorOutfitSlot* TargetSlot;
};
