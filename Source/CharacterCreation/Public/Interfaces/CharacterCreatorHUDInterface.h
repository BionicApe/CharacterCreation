// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "CharacterCreatorHUDInterface.generated.h"

class UInventory;
class AInventoryStore;

/**
*
*/
UINTERFACE(Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class ICharacterCreatorHUDInterface
{
	GENERATED_BODY()

public:

	virtual void OpenCharacterCreator() = 0;
};