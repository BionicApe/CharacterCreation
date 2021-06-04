// Created by Bionic Ape. All Rights Reserved.


#include "Subsystems/CharacterCreationSubsystem.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <CharacterCreatorOutfitsSet.h>
#include <CharacterCreatorOutfit.h>
#include <CharacterCreationTypes.h>
#include <CharacterCreatorOutfitSlot.h>
#include "Engine/GameInstance.h"

static const FString ContextString(TEXT("Character Creation"));
DEFINE_LOG_CATEGORY(CharacterCreationLog);

void UCharacterCreationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		for (UGameInstanceSubsystem* Subsystem : GameInstance->GetSubsystemArray<UGameInstanceSubsystem>())
		{
			if (ICharacterCreationDAO* CCDao = Cast<ICharacterCreationDAO>(Subsystem))
			{
				Dao = CCDao;
				break;
			}
		}
	}
}