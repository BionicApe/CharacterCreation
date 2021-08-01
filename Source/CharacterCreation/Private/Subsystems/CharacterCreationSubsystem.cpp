// Created by Bionic Ape. All Rights Reserved.


#include "Subsystems/CharacterCreationSubsystem.h"
#include "Engine/GameInstance.h"

static const FString ContextString(TEXT("Character Creation"));
DEFINE_LOG_CATEGORY(CharacterCreationLog);

void UCharacterCreationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DaoOwner = Cast<ICharacterCreationDAOOwner>(GetGameInstance());

	if (!DaoOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("UCharacterCreationSubsystem::Initialize() Game Instance Doesn't implement ICharacterCreationDAOOwner!!"));
	}
}