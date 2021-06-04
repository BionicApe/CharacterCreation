// Move 36 Studio

#pragma once

#include "UObject/Interface.h"
#include "CharacterCreatable.generated.h"

struct FCharacterCreation;
struct FCharacterCreationBodyParts;

/**
*
*/
UINTERFACE(Blueprintable)
class CHARACTERCREATION_API UCharacterCreatable : public UInterface
{
	GENERATED_BODY()
};

class ICharacterCreatable
{
	GENERATED_BODY()

public:

	virtual FCharacterCreation* GetCharacterCreation() = 0;

	virtual FCharacterCreationBodyParts* GetBodyParts() = 0;
};