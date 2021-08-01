// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/CharacterCreationDAO.h"
#include "CharacterCreationSubsystem.generated.h"

class ICharacterCreationDAO;

DECLARE_LOG_CATEGORY_EXTERN(CharacterCreationLog, Warning, All);

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	ICharacterCreationDAOOwner* DaoOwner;

public:

	void Initialize(FSubsystemCollectionBase& Collection) override;

	ICharacterCreationDAO* GetDao() const { return DaoOwner ? DaoOwner->GetCharacterCreationDAO() : nullptr; }
};
