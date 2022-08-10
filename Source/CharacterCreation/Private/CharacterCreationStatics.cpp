// Created by Bionic Ape. All Rights Reserved.

#include "CharacterCreationStatics.h"
#include "Misc/FileHelper.h"
#include "UObject/UObjectGlobals.h"
#include "CharacterCreator.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorMatAttribute.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorGroom.h"
#include "CharacterCreatorOutfitSlot.h"
#include "CharacterCreatorModel.h"



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
	//TODO: INITIAL MODEL ASIGNMENT


	//Used to create assets
	bool bIsCreatingAsset = Outer && Outer->IsA<UPackage>();
	//End Used to create assets

	UCharacterCreator* CharacterCreator = NewObject<UCharacterCreator>(Outer, UCharacterCreator::StaticClass(), bIsCreatingAsset ? CharacterCreatorName : NAME_None, (EObjectFlags)InFlags);
	CharacterCreator->Id = CharacterCreatorName.ToString();

	//Validation Model
	{
		//Actual model load
		FString const ModelID = JsonCharacterCreator->GetStringField(TEXT("Model"));
		UCharacterCreatorModel* Model = LoadObject<UCharacterCreatorModel>(nullptr, *ModelID);
		
		if (!Model)
		{
			//Load default metahuman model if there is no model on the data base
			FString const MHModelID = TEXT("/Game/ThePrisonCC/CharacterCreation/Models/Metahuman/CM_Metahuman.CM_Metahuman");
			Model = LoadObject<UCharacterCreatorModel>(nullptr, *ModelID);
			CharacterCreator->Model = Model;
		}

		CharacterCreator->Model = Model;
	}


	//Morph Target Attributes
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

	//Material Attributes
	for (const TSharedPtr<FJsonValue>& AttributeJsonValue : JsonCharacterCreator->GetArrayField(TEXT("MaterialAttributeValues")))
	{
		TSharedPtr<FJsonObject> AttributeJson = AttributeJsonValue->AsObject();

		FString const AttributeId = AttributeJson->GetStringField(TEXT("MaterialAttribute"));

		UCharacterCreatorMatAttribute* Attribute = LoadObject<UCharacterCreatorMatAttribute>(nullptr, *AttributeId);
		if (!Attribute)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorMaterialAttribute with ID: %s"), *AttributeId);
			continue;
		}

		float const AttributeValue = AttributeJson->GetNumberField(TEXT("Value"));

		TArray<UCharacterCreatorOutfitSlot*> AffectedSlots;
		for (const TSharedPtr<FJsonValue>& AffectedSlotsJsonValue : AttributeJson->GetArrayField(TEXT("AffectedSlots")))
		{
			TSharedPtr<FJsonObject> AffectedSlotsJsonObject = AffectedSlotsJsonValue->AsObject();
			FString const SlotID = AffectedSlotsJsonObject->GetStringField(TEXT("Slot"));
			UCharacterCreatorOutfitSlot* Slot = LoadObject<UCharacterCreatorOutfitSlot>(nullptr, *SlotID);

			AffectedSlots.Add(Slot);
		}

		CharacterCreator->MaterialAttributeValues.Emplace(Attribute, AttributeValue, AffectedSlots);
	}

	//Outfits
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

		//Validation model slot check
		if (CharacterCreator->Model && !CharacterCreator->Model->ContainsSlot(Slot))
		{
			UE_LOG(LogTemp, Error, TEXT("The UCharacterCreatorOutfitSlot with ID: %s is not valid for the current model"), *SlotID);
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

	//Grooms
	for (const TSharedPtr<FJsonValue>& GroomJsonValue : JsonCharacterCreator->GetArrayField(TEXT("SlotAndGroomArray")))
	{
		const TSharedPtr<FJsonObject>& GroomJson = GroomJsonValue->AsObject();
		FString const SlotID = GroomJson->GetStringField(TEXT("Slot"));

		UCharacterCreatorOutfitSlot* Slot = LoadObject<UCharacterCreatorOutfitSlot>(nullptr, *SlotID);
		if (!Slot)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorGroomSlot with ID: %s"), *SlotID);
			continue;
		}

		//Validation model slot check
		if (CharacterCreator->Model && !CharacterCreator->Model->ContainsSlot(Slot))
		{
			UE_LOG(LogTemp, Error, TEXT("The UCharacterCreatorOutfitSlot with ID: %s is not valid for the current model"), *SlotID);
			continue;
		}

		FString const GroomID = GroomJson->GetStringField(TEXT("Groom"));

		UCharacterCreatorGroom* Groom = LoadObject<UCharacterCreatorGroom>(nullptr, *GroomID);
		if (!Groom)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't load UCharacterCreatorGroom with ID: %s"), *GroomID);
			continue;
		}
		CharacterCreator->SlotAndGroomArray.Emplace(Slot, Groom);
	}

	{//BodyType
		CharacterCreator->BodyType = (FCharacterCreationBodyType)JsonCharacterCreator->GetIntegerField(TEXT("BodyType"));
	}//End: BodyType

	return CharacterCreator;
}

TSharedPtr<FJsonObject> UCharacterCreationStatics::ToJson(UCharacterCreator* CharacterCreator)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (!CharacterCreator)
	{
		UE_LOG(LogTemp, Error, TEXT("UCharacterCreationStatics::ToJson() Character Creator is nullptr"));
		return JsonObject;
	}

	JsonObject->SetStringField(TEXT("PK"), CharacterCreator->Id);
	JsonObject->SetStringField(TEXT("SK"), TEXT("CharacterCreator"));

	{//SlotAndOutfit
		TArray<TSharedPtr<FJsonValue>> SlotAndOutfitArray;
		for (const FCCSlotAndOutfit& SlotAndOutfit : CharacterCreator->SlotAndOutfitArray)
		{
			//Validation model slot check //Do we need to check when saving and loading? Maybe not, but the system is more reliable this way
			if (CharacterCreator->Model && !CharacterCreator->Model->ContainsSlot(SlotAndOutfit.Slot))
			{
				FString const SlotID = UKismetSystemLibrary::GetPathName(SlotAndOutfit.Slot);
				UE_LOG(LogTemp, Error, TEXT("The UCharacterCreatorOutfitSlot with ID: %s is not valid for the current model"), *SlotID);
				continue;
			}

			TSharedPtr<FJsonObject> JsonObjectEntry = MakeShareable(new FJsonObject());
			JsonObjectEntry->SetStringField(TEXT("Slot"), UKismetSystemLibrary::GetPathName(SlotAndOutfit.Slot));
			JsonObjectEntry->SetStringField(TEXT("Outfit"), UKismetSystemLibrary::GetPathName(SlotAndOutfit.Outfit));
			SlotAndOutfitArray.Add(MakeShareable(new FJsonValueObject(JsonObjectEntry)));
		}

		JsonObject->SetArrayField(TEXT("SlotAndOutfitArray"), SlotAndOutfitArray);
	}//End: SlotAndOutfit

	{//SlotAndGroom
		TArray<TSharedPtr<FJsonValue>> SlotAndGroomArray;
		for (const FCCSlotAndGroom& SlotAndGroom : CharacterCreator->SlotAndGroomArray)
		{
			//Validation model slot check //Do we need to check when saving and loading? Maybe not, but the system is more reliable this way
			if (CharacterCreator->Model && !CharacterCreator->Model->ContainsSlot(SlotAndGroom.Slot))
			{
				FString const SlotID = UKismetSystemLibrary::GetPathName(SlotAndGroom.Slot);
				UE_LOG(LogTemp, Error, TEXT("The UCharacterCreatorOutfitSlot with ID: %s is not valid for the current model"), *SlotID);
				continue;
			}

			TSharedPtr<FJsonObject> JsonObjectEntry = MakeShareable(new FJsonObject());
			JsonObjectEntry->SetStringField(TEXT("Slot"), UKismetSystemLibrary::GetPathName(SlotAndGroom.Slot));
			JsonObjectEntry->SetStringField(TEXT("Groom"), UKismetSystemLibrary::GetPathName(SlotAndGroom.Groom));
			SlotAndGroomArray.Add(MakeShareable(new FJsonValueObject(JsonObjectEntry)));
		}

		JsonObject->SetArrayField(TEXT("SlotAndGroomArray"), SlotAndGroomArray);
	}//End: SlotAndGroom

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

	{//MaterialAttributeValues
		TArray<TSharedPtr<FJsonValue>> MaterialAttributeValues;
		for (const FCCMaterialAttributeValue& MaterialAttributeValue : CharacterCreator->MaterialAttributeValues)
		{
			TSharedPtr<FJsonObject> JsonObjectEntry = MakeShareable(new FJsonObject());
			JsonObjectEntry->SetStringField(TEXT("MaterialAttribute"), UKismetSystemLibrary::GetPathName(MaterialAttributeValue.MaterialAttribute));
			JsonObjectEntry->SetNumberField(TEXT("Value"), MaterialAttributeValue.Value);

			TArray<TSharedPtr<FJsonValue>> AffectedSlots;
			for (const UCharacterCreatorOutfitSlot* AffectedSlot : MaterialAttributeValue.AffectedSlots)
			{
				TSharedPtr<FJsonObject> JsonObjectSubEntry = MakeShareable(new FJsonObject());
				JsonObjectSubEntry->SetStringField(TEXT("Slot"), UKismetSystemLibrary::GetPathName(AffectedSlot));
				AffectedSlots.Add(MakeShareable(new FJsonValueObject(JsonObjectSubEntry)));
			}
			JsonObjectEntry->SetArrayField(TEXT("AffectedSlots"), AffectedSlots);

			MaterialAttributeValues.Add(MakeShareable(new FJsonValueObject(JsonObjectEntry)));
		}
		JsonObject->SetArrayField(TEXT("MaterialAttributeValues"), MaterialAttributeValues);
	}//End: MaterialAttributeValues

	{//BodyType
		JsonObject->SetNumberField(TEXT("BodyType"), (double)CharacterCreator->BodyType); //Will this cause errors due to int to double conversion?
	}//End: BodyType

	{//Validation Model
		JsonObject->SetStringField(TEXT("Model"), UKismetSystemLibrary::GetPathName(CharacterCreator->Model));
	}//End: Validation Model

	return JsonObject;
}
