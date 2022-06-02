// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreationStatics.h"
#include "Misc/FileHelper.h"
#include "UObject/UObjectGlobals.h"
#include "CharacterCreator.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorOutfitSlot.h"



UCharacterCreator* UCharacterCreationStatics::LoadFromJsonFile(UClass* InClass, const FString& FilePath, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName)
{
	FString CharacterCreatorJsonString;
	FFileHelper::LoadFileToString(CharacterCreatorJsonString, *FilePath);
	return LoadFromJsonString(InClass, CharacterCreatorJsonString, Outer, InFlags, CharacterCreatorName);
}

UCharacterCreator* UCharacterCreationStatics::LoadFromJsonString(UClass* InClass, const FString& JsonObjString, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonObjString);
	FJsonSerializer::Deserialize(JsonReader, JsonObject);
	return LoadFromJson(InClass, JsonObject, Outer, InFlags, CharacterCreatorName);
}

UCharacterCreator* UCharacterCreationStatics::LoadFromJson(UClass* InClass, TSharedPtr<FJsonObject> JsonCharacterCreator, UObject* Outer, uint8 InFlags, const FName& CharacterCreatorName)
{

	//Used to create assets
	bool bIsCreatingAsset = Outer && Outer->IsA<UPackage>();
	//End Used to create assets

	UCharacterCreator* CharacterCreator = NewObject<UCharacterCreator>(Outer, UCharacterCreator::StaticClass(), bIsCreatingAsset ? CharacterCreatorName : NAME_None, (EObjectFlags)InFlags);
	CharacterCreator->Id = CharacterCreatorName.ToString();

	for (const TSharedPtr<FJsonValue>& AttributeJsonValue : JsonCharacterCreator->GetArrayField(TEXT("AttributeValues")))
	{
		TSharedPtr<FJsonObject> AttributeJson = AttributeJsonValue->AsObject();

		FString const AttributeId = AttributeJson->GetStringField(TEXT("Attribute"));

		UCharacterCreatorAttribute* Attribute = LoadObject<UCharacterCreatorAttribute>(nullptr, *AttributeId);
		if (!Attribute)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorAttribute with ID: %s"), *AttributeId);
			continue;
		}

		float const AttributeValue = AttributeJson->GetNumberField(TEXT("Value"));
		CharacterCreator->AttributeValues.Emplace(Attribute, AttributeValue);
	}

	for (const TSharedPtr<FJsonValue>& OutfitJsonValue : JsonCharacterCreator->GetArrayField(TEXT("SlotAndOutfitArray")))
	{
		const TSharedPtr<FJsonObject>& OutfitJson = OutfitJsonValue->AsObject();
		FString const SlotID = OutfitJson->GetStringField(TEXT("Slot"));

		UCharacterCreatorOutfitSlot* Slot = LoadObject<UCharacterCreatorOutfitSlot>(nullptr, *SlotID);
		if (!Slot)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorOutfitSlot with ID: %s"), *SlotID);
			continue;
		}

		FString const OutfitID = OutfitJson->GetStringField(TEXT("Outfit"));

		UCharacterCreatorOutfit* Outfit = LoadObject<UCharacterCreatorOutfit>(nullptr, *OutfitID);
		if (!Outfit)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorOutfit with ID: %s"), *OutfitID);
			continue;
		}
		CharacterCreator->SlotAndOutfitArray.Emplace(Slot, Outfit);
	}
	return CharacterCreator;
}

TSharedPtr<FJsonObject> UCharacterCreationStatics::ToJson(UCharacterCreator* CharacterCreator)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("PK"), CharacterCreator->Id);
	JsonObject->SetStringField(TEXT("SK"), TEXT("CharacterCreator"));

	{//SlotAndOutfit
		TArray<TSharedPtr<FJsonValue>> SlotAndOutfitArray;
		for (const FCCSlotAndOutfit& SlotAndOutfit : CharacterCreator->SlotAndOutfitArray)
		{
			TSharedPtr<FJsonObject> JsonObjectEntry = MakeShareable(new FJsonObject());
			JsonObjectEntry->SetStringField(TEXT("Slot"), UKismetSystemLibrary::GetPathName(SlotAndOutfit.Slot));
			JsonObjectEntry->SetStringField(TEXT("Outfit"), UKismetSystemLibrary::GetPathName(SlotAndOutfit.Outfit));
			SlotAndOutfitArray.Add(MakeShareable(new FJsonValueObject(JsonObjectEntry)));
		}
		JsonObject->SetArrayField(TEXT("SlotAndOutfitArray"), SlotAndOutfitArray);
	}//End: SlotAndOutfit

	{//AttributeValues
		TArray<TSharedPtr<FJsonValue>> AttributeValues;
		for (const FCCAttributeValue& AttributeValue : CharacterCreator->AttributeValues)
		{
			TSharedPtr<FJsonObject> JsonObjectEntry = MakeShareable(new FJsonObject());
			JsonObjectEntry->SetStringField(TEXT("Attribute"), UKismetSystemLibrary::GetPathName(AttributeValue.Attribute));
			JsonObjectEntry->SetNumberField(TEXT("Value"), AttributeValue.Value);
			AttributeValues.Add(MakeShareable(new FJsonValueObject(JsonObjectEntry)));
		}
		JsonObject->SetArrayField(TEXT("AttributeValues"), AttributeValues);
	}//End: AttributeValues

	return JsonObject;
}
