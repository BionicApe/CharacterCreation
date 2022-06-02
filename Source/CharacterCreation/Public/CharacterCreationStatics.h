// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "CharacterCreationStatics.generated.h"

class UCharacterCreator;


UCLASS()
class CHARACTERCREATION_API UCharacterCreationStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Character Creation")
	static UCharacterCreator* LoadFromJsonFile(UClass* InClass, const FString& FilePath, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName);

	UFUNCTION(BlueprintCallable, Category = "Character Creation")
	static UCharacterCreator* LoadFromJsonString(UClass* InClass, const FString& JsonObjString, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName);

	//UFUNCTION(BlueprintCallable, Category = "Character Creation")
	static UCharacterCreator* LoadFromJson(UClass* InClass, TSharedPtr<FJsonObject> JsonCharacterCreator, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName);

	static TSharedPtr<FJsonObject> ToJson(UCharacterCreator* CharacterCreator);

};