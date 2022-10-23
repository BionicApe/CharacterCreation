// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreatorAttribute.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorAttribute : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	FName MorphName;

	UPROPERTY(EditInstanceOnly)
	FName FriendlyName;

	UPROPERTY(EditInstanceOnly)
	float MorphMin = -1.f;

	UPROPERTY(EditInstanceOnly)
	float MorphMax = 1.f;

	UPROPERTY(EditInstanceOnly)
	FString DatabaseColumnName;
};
