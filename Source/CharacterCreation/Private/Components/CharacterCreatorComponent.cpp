// Created by Bionic Ape. All rights reseved.


#include "Components/CharacterCreatorComponent.h"
#include "Subsystems/CharacterCreationSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "CharacterCreator.h"
#include "CharacterCreationTypes.h"
#include "Net/UnrealNetwork.h"

UCharacterCreatorComponent::UCharacterCreatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterCreatorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterCreatorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreatorComponent, CharacterCreation);
	//DOREPLIFETIME(UCharacterCreatorComponent, BodyPartsComponents);//no need for it
}

void UCharacterCreatorComponent::OnRep_CharacterCreation()
{
	LoadCharacterCreator();
}


#if WITH_EDITOR
void UCharacterCreatorComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName().Equals("CharacterCreator"))
	{
		if (CharacterCreator)
		{
			CharacterCreation = CharacterCreator->CharacterCreation;
			LoadCharacterCreator();
		}
	}
}
#endif // WITH_EDITOR


void UCharacterCreatorComponent::ApplyNewCharacterCreator(FCharacterCreation const& NewCharacterCreation)
{
	if (!bCustomCharacter)
	{
		CharacterCreation = NewCharacterCreation;
		LoadCharacterCreator();
	}
}

void UCharacterCreatorComponent::SetupBodyParts(USkeletalMeshComponent* Head, USkeletalMeshComponent* Bottom, USkeletalMeshComponent* Upper)
{
	BodyPartsComponents.Head = Head;
	BodyPartsComponents.UpperBody = Upper;
	BodyPartsComponents.LowerBody = Bottom;
}

void UCharacterCreatorComponent::LoadCharacterCreator(UCharacterCreator* NewCharacterCreator /*= nullptr*/)
{
	if (NewCharacterCreator)
	{
		SetCharacterCreator(NewCharacterCreator);
	}

	if (!bCustomCharacter)
	{
		if (bLoadFromMain)
		{
			UCharacterCreationSubsystem* CCSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCharacterCreationSubsystem>();
			CharacterCreation = CCSubsystem->MainCharacterCreation;
		}
		if (GetWorld() && GetWorld()->GetGameInstance())
		{
			UCharacterCreationSubsystem* CCSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCharacterCreationSubsystem>();
			CCSubsystem->ApplyFromFromCharacterCreation(CharacterCreation, BodyPartsComponents);
		}
	}
}

void UCharacterCreatorComponent::SetCharacterCreator(UCharacterCreator* NewCharacterCreator)
{
	CharacterCreator = NewCharacterCreator;

	if (CharacterCreator)
	{
		CharacterCreation = CharacterCreator->CharacterCreation;
	}
}