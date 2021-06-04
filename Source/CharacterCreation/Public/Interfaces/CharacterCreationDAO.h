// Move 36 Studio

#pragma once

#include "UObject/Interface.h"
#include "CharacterCreationDAO.generated.h"


class UCharacterCreator;

USTRUCT(BlueprintType, Blueprintable)
struct CHARACTERCREATION_API FAsyncCharacterCreatorResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bIsSuccessful = false;

	UPROPERTY(BlueprintReadOnly)
	UCharacterCreator* CharacterCreator;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorMessage;

	FAsyncCharacterCreatorResponse() : CharacterCreator(nullptr){}

	FAsyncCharacterCreatorResponse(UCharacterCreator* InCharacterCreator, const FString& InErrorMessage) : CharacterCreator(InCharacterCreator), ErrorMessage(InErrorMessage){}
};

//DECLARE_DELEGATE_OneParam(FAsyncLoadCharacterCreatorDelegate, FAsyncCharacterCreatorResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncLoadCharacterCreatorDelegate, FAsyncCharacterCreatorResponse, Response);
//DECLARE_DELEGATE_OneParam(FAsyncSaveCharacterCreatorDelegate, FAsyncCharacterCreatorResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncSaveCharacterCreatorDelegate, FAsyncCharacterCreatorResponse, Response);

/**
*
*/
UINTERFACE(Blueprintable)
class CHARACTERCREATION_API UCharacterCreationDAO : public UInterface
{
	GENERATED_BODY()

};

class ICharacterCreationDAO
{
	GENERATED_BODY()

public:

	virtual void SaveCharacterCreator(UCharacterCreator* CharacterCreator, FAsyncSaveCharacterCreatorDelegate Delegate) = 0;

	virtual void LoadCharacterCreator(int32 Id, FAsyncLoadCharacterCreatorDelegate Delegate) = 0;
};