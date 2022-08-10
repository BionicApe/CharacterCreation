// Created by Bionic Ape. All rights reseved.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CharacterCreationTypes.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UCharacterCreatorOutfitSlot;
class UCharacterCreatorOutfit;
class UCharacterCreatorGroom;
class UCharacterCreatorAttribute;
class UCharacterCreatorMatAttribute;



USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCCSlotAndOutfit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorOutfitSlot* Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorOutfit* Outfit;

	FCCSlotAndOutfit() : Slot(nullptr), Outfit(nullptr) {}

	FCCSlotAndOutfit(UCharacterCreatorOutfitSlot* NewSlot, UCharacterCreatorOutfit* NewValue) : Slot(NewSlot), Outfit(NewValue) {}
};

USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCCSlotAndGroom
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorOutfitSlot* Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorGroom* Groom;

	FCCSlotAndGroom() : Slot(nullptr), Groom(nullptr) {}

	FCCSlotAndGroom(UCharacterCreatorOutfitSlot* NewSlot, UCharacterCreatorGroom* NewValue) : Slot(NewSlot), Groom(NewValue) {}
};

USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCCMeshCompSlotOutfit
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterCreator)
	USkeletalMeshComponent* SkComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorOutfitSlot* Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorOutfit* Value;

	FCCMeshCompSlotOutfit() : SkComp(nullptr), Slot(nullptr), Value(nullptr) {}

	FCCMeshCompSlotOutfit(USkeletalMeshComponent* NewSkComp, UCharacterCreatorOutfitSlot* NewSlot, UCharacterCreatorOutfit* NewValue) : SkComp(NewSkComp), Slot(NewSlot), Value(NewValue) {}
};

USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCCAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorAttribute* Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	float Value;


	FCCAttributeValue() :Attribute(nullptr), Value(0.f) {}

	FCCAttributeValue(UCharacterCreatorAttribute* NewAttribute, float NewValue) :Attribute(NewAttribute), Value(NewValue) {}
};

USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCCMaterialAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	UCharacterCreatorMatAttribute* MaterialAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	TArray<UCharacterCreatorOutfitSlot*> AffectedSlots;

	//FCCMaterialAttributeValue() :MaterialAttribute(nullptr), Value(0.f){}
	FCCMaterialAttributeValue() :MaterialAttribute(nullptr), Value(0.f), AffectedSlots(){}

	//Legacy, migth dissapear
	FCCMaterialAttributeValue(UCharacterCreatorMatAttribute* NewAttribute, float NewValue) :MaterialAttribute(NewAttribute), Value(NewValue){}
	FCCMaterialAttributeValue(UCharacterCreatorMatAttribute* NewAttribute, float NewValue, TArray<UCharacterCreatorOutfitSlot*> NewAffectedSlots) :MaterialAttribute(NewAttribute), Value(NewValue), AffectedSlots(NewAffectedSlots){}
};


//
///** Struct representing a slot for an item, shown in the UI */
//USTRUCT(BlueprintType)
//struct CHARACTERCREATION_API FCharacterCreation : public FTableRowBase
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	int32 HeadId;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	int32 UpperBodyId;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	int32 BottomBodyId;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	TArray<FCCSlotAndOutfit> SlotValues;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//TMap<FName, FMorphPresetData> MorphPresetData;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData Bodybuilder = FMorphPresetData("CC_Bodybuilder", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData BodyTone = FMorphPresetData("CC_BodyTone", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData Heavy = FMorphPresetData("CC_Heavy", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData Old = FMorphPresetData("CC_Old", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData Thin = FMorphPresetData("CC_Thin", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadFaceAngle = FMorphPresetData("CC_Head_FaceAngle", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadCheekBonesSize = FMorphPresetData("CC_Head_CheekBonesSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadFaceDepth = FMorphPresetData("CC_Head_FaceDepth", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadEarLobeSize = FMorphPresetData("CC_Head_EarLobeSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadEarSize = FMorphPresetData("CC_Head_EarSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadEyeSize = FMorphPresetData("CC_Head_EyeSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadHeart = FMorphPresetData("CC_Head_Heart", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadHeavy = FMorphPresetData("CC_Head_Heavy", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadJawSize = FMorphPresetData("CC_Head_JawSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadLipSize = FMorphPresetData("CC_Head_LipSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadMouthSize = FMorphPresetData("CC_Head_MouthSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadNarrow = FMorphPresetData("CC_Head_Narrow", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadNoseSize = FMorphPresetData("CC_Head_NoseSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadOld = FMorphPresetData("CC_Head_Old", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadRound = FMorphPresetData("CC_Head_Round", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadSquare = FMorphPresetData("CC_Head_Square", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadThin = FMorphPresetData("CC_Head_Thin", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
//	//FMorphPresetData HeadYoung = FMorphPresetData("CC_Head_Young", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f);
//
//	FCharacterCreation()
//	{
//		HeadId = 0;
//		UpperBodyId = 0;
//		BottomBodyId = 0;
//
//		//MorphPresetData.Reserve(23);
//		//MorphPresetData.Add("CC_Bodybuilder", FMorphPresetData("CC_Bodybuilder", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_BodyTone", FMorphPresetData("CC_BodyTone", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Heavy", FMorphPresetData("CC_Heavy", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Old", FMorphPresetData("CC_Old", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Thin", FMorphPresetData("CC_Thin", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_FaceAngle", FMorphPresetData("CC_Head_FaceAngle", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_CheekBonesSize", FMorphPresetData("CC_Head_CheekBonesSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_FaceDepth", FMorphPresetData("CC_Head_FaceDepth", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_EarLobeSize", FMorphPresetData("CC_Head_EarLobeSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_EarSize", FMorphPresetData("CC_Head_EarSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_EyeSize", FMorphPresetData("CC_Head_EyeSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Heart", FMorphPresetData("CC_Head_Heart", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Heavy", FMorphPresetData("CC_Head_Heavy", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_JawSize", FMorphPresetData("CC_Head_JawSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_LipSize", FMorphPresetData("CC_Head_LipSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_MouthSize", FMorphPresetData("CC_Head_MouthSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Narrow", FMorphPresetData("CC_Head_Narrow", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_NoseSize", FMorphPresetData("CC_Head_NoseSize", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Old", FMorphPresetData("CC_Head_Old", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Round", FMorphPresetData("CC_Head_Round", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Square", FMorphPresetData("CC_Head_Square", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Thin", FMorphPresetData("CC_Head_Thin", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//		//MorphPresetData.Add("CC_Head_Young", FMorphPresetData("CC_Head_Young", 0.f, /*InbBlacklist*/false, /*InbBake*/true, /*InRandMin*/0.f, /*InRandMax*/1.f));
//	}
//
//	UCharacterCreatorOutfit* GetOutfitForSlot(UCharacterCreatorOutfitSlot* Slot)
//	{
//		for (FCCSlotAndOutfit& SlotValue : SlotValues)
//		{
//			if (SlotValue.Slot == Slot)
//			{
//				return SlotValue.Value;
//			}
//		}
//		return nullptr;
//	}
//};

USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCharacterCreationBodyParts
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	USkeletalMeshComponent* Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	USkeletalMeshComponent* UpperBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	USkeletalMeshComponent* LowerBody;

	FCharacterCreationBodyParts()
	{
		Head = nullptr;
		UpperBody = nullptr;
		LowerBody = nullptr;
	}
};


/** Struct representing a slot for an item, shown in the UI */
USTRUCT(BlueprintType)
struct CHARACTERCREATION_API FCharacterCreationMesh : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	int32 MeshId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	USkeletalMesh* Mesh;

	FCharacterCreationMesh()
	{
		MeshId = 0;
		Mesh = nullptr;
	}
};

UENUM(BlueprintType)
enum class FCharacterCreationBodyType : uint8
{
	NormalWeight = 0,
	OverWeight,
	UnderWeight,
	MAX
};