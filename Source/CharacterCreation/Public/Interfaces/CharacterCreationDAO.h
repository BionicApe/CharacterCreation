// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "CharacterCreationDAO.generated.h"


class UCharacterCreator;
class ICharacterCreationDAO;

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

	//static ICharacterCreationDAO* DaoInstance;

public:

	virtual void SaveCharacterCreator(UCharacterCreator* CharacterCreator, FAsyncSaveCharacterCreatorDelegate Delegate) = 0;

	virtual void LoadCharacterCreator(int32 Id, FAsyncLoadCharacterCreatorDelegate Delegate) = 0;
};

#pragma region DAOOwner

/**
*
* This class needs to be implemented by the GameInstance, it would hold provide class that implements ICharacterCreationDAO
* 
*/
UINTERFACE(Blueprintable)
class CHARACTERCREATION_API UCharacterCreationDAOOwner : public UInterface
{
	GENERATED_BODY()

};

/**
*
* This class needs to be implemented by the GameInstance, it would hold provide class that implements ICharacterCreationDAO
*
*/
class ICharacterCreationDAOOwner
{
	GENERATED_BODY()

public:

	virtual ICharacterCreationDAO* GetCharacterCreationDAO() const = 0;
	virtual void SetCharacterCreationDAO(ICharacterCreationDAO* Dao) = 0;
};

#pragma endregion