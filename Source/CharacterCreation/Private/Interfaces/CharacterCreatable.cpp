


#include "Interfaces/CharacterCreatable.h"

UCharacterCreatable::UCharacterCreatable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FCharacterCreation* ICharacterCreatable::GetCharacterCreation()
{
	return nullptr;
}

FCharacterCreationBodyParts* ICharacterCreatable::GetBodyParts()
{
	return nullptr;
}
