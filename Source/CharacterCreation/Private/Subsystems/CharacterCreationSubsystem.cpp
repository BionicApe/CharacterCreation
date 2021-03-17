// Created by Bionic Ape. All Rights Reserved.


#include "Subsystems/CharacterCreationSubsystem.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <CharacterCreatorOutfitsSet.h>
#include <CharacterCreatorOutfit.h>
#include <CharacterCreationTypes.h>
#include <CharacterCreatorOutfitSlot.h>

static const FString ContextString(TEXT("Character Creation"));
DEFINE_LOG_CATEGORY(CharacterCreationLog);


UCharacterCreationSubsystem::UCharacterCreationSubsystem() : Super()
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> CharacterCreationsDT(TEXT("DataTable'/Game/ThePrison/Data/DT_CharacterCreations.DT_CharacterCreations'"));
	//CharacterCreations = CharacterCreationsDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> HeadMeshesDT(TEXT("DataTable'/Game/ThePrisonCC/CharacterCreation/DT_CCHeadMeshes.DT_CCHeadMeshes'"));
	HeadMeshes = HeadMeshesDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> UpperBodyMeshesDT(TEXT("DataTable'/Game/ThePrisonCC/CharacterCreation/DT_CCUpperBodyMeshes.DT_CCUpperBodyMeshes'"));
	UpperBodyMeshes = UpperBodyMeshesDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> BottomBodyMeshesDT(TEXT("DataTable'/Game/ThePrisonCC/CharacterCreation/DT_CCBottomBodyMeshes.DT_CCBottomBodyMeshes'"));
	BottomBodyMeshes = BottomBodyMeshesDT.Object;

	static ConstructorHelpers::FObjectFinder<UCharacterCreatorOutfitsSet> BBOutfitRef(TEXT("CharacterCreatorOutfitsSet'/Game/ThePrisonCC/CharacterCreation/Outfits/OS_BottomBody.OS_BottomBody'"));
	BottomBodyOutfits = BBOutfitRef.Object;

	static ConstructorHelpers::FObjectFinder<UCharacterCreatorOutfitsSet> UBOutfitRef(TEXT("CharacterCreatorOutfitsSet'/Game/ThePrisonCC/CharacterCreation/Outfits/OS_UpperBody.OS_UpperBody'"));
	UpperBodyOutfits = UBOutfitRef.Object;

	static ConstructorHelpers::FObjectFinder<UCharacterCreatorOutfitsSet> HeadOutfitRef(TEXT("CharacterCreatorOutfitsSet'/Game/ThePrisonCC/CharacterCreation/Outfits/OS_HeadOutfits.OS_HeadOutfits'"));
	HeadOutfits = HeadOutfitRef.Object;
}

USkeletalMesh* UCharacterCreationSubsystem::CreateSkeletalMesh(FCharacterCreation const& CharacterCreation)
{
	//FCharacterCreationMesh* CCMUpperBody = UpperBodyMeshes->FindRow<FCharacterCreationMesh>(*FString::FromInt(CharacterCreation.UpperBodyId), ContextString, true);
	//FCharacterCreationMesh* CCMBottomBody = BottomBodyMeshes->FindRow<FCharacterCreationMesh>(*FString::FromInt(CharacterCreation.BottomBodyId), ContextString, true);
	//FCharacterCreationMesh* CCMHead = HeadMeshes->FindRow<FCharacterCreationMesh>(*FString::FromInt(CharacterCreation.HeadId), ContextString, true);


	//if (CCMUpperBody && CCMBottomBody && CCMHead)
	//{
	//	//USkeletalMesh* UpperBodyBakedMesh = FRuntimeMorphBaker::BakeMorphs(CCMUpperBody->Mesh, BulkMatchSettings, CharacterCreation.MorphPresetData);
	//	//USkeletalMesh* BottomBodyBakedMesh = FRuntimeMorphBaker::BakeMorphs(CCMBottomBody->Mesh, BulkMatchSettings, CharacterCreation.MorphPresetData);
	//	//USkeletalMesh* HeadBakedMesh = FRuntimeMorphBaker::BakeMorphs(CCMHead->Mesh, BulkMatchSettings, CharacterCreation.MorphPresetData);

	//	FSkeletalMeshMergeParams SkeletalMeshMergeParams;
	//	SkeletalMeshMergeParams.MeshesToMerge.Add(HeadBakedMesh);
	//	SkeletalMeshMergeParams.MeshesToMerge.Add(UpperBodyBakedMesh);
	//	SkeletalMeshMergeParams.MeshesToMerge.Add(BottomBodyBakedMesh);
	//	SkeletalMeshMergeParams.Skeleton = CCMHead->Mesh->Skeleton;

	//	CharacterCreations->AddRow(*FString::FromInt(CharacterCreations->GetRowMap().Num()), CharacterCreation);

	//	USkeletalMesh* GeneratedMesh = UMeshMergeFunctionLibrary::MergeMeshes(SkeletalMeshMergeParams);
	//	return GeneratedMesh;
	//}

	return nullptr;
}

USkeletalMesh* UCharacterCreationSubsystem::GetHeadMesh(int32 id)
{
	//FCharacterCreationMesh* Row = HeadMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	//if (Row)
	//{
	//	return Row->Mesh;
	//}

	if (HeadOutfits && HeadOutfits->Outfits.IsValidIndex(id))
	{
		return HeadOutfits->Outfits[0]->Mesh;
	}

	return nullptr;
}

USkeletalMesh* UCharacterCreationSubsystem::GetBottomBodyMesh(int32 id)
{
	//FCharacterCreationMesh* Row = BottomBodyMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	//if (Row)
	//{
	//	return Row->Mesh;
	//}

	if (BottomBodyOutfits && BottomBodyOutfits->Outfits.IsValidIndex(id))
	{
		return BottomBodyOutfits->Outfits[0]->Mesh;
	}
	return nullptr;
}

USkeletalMesh* UCharacterCreationSubsystem::GetUpperBodyMesh(int32 id)
{
	//FCharacterCreationMesh* Row = UpperBodyMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	//if (Row)
	//{
	//	return Row->Mesh;
	//}


	if (UpperBodyOutfits && UpperBodyOutfits->Outfits.IsValidIndex(id))
	{
		return UpperBodyOutfits->Outfits[0]->Mesh;
	}

	return nullptr;
}

void UCharacterCreationSubsystem::SetFromCharacterCreation(FCharacterCreation const& CharacterCreation, USkeletalMeshComponent* Head, USkeletalMeshComponent* BottomBody, USkeletalMeshComponent* UpperBody)
{
	//if (Head)
	//{
	//	USkeletalMesh* OriginalMesh = GetHeadMesh(CharacterCreation.HeadId);
	//	USkeletalMesh* HeadBakedMesh = FRuntimeMorphBaker::BakeMorphs(OriginalMesh, BulkMatchSettings, CharacterCreation.MorphPresetData);
	//	Head->SetSkeletalMesh(HeadBakedMesh);
	//}
	//if (BottomBody)
	//{
	//	USkeletalMesh* OriginalMesh = GetBottomBodyMesh(CharacterCreation.BottomBodyId);
	//	USkeletalMesh* BottomBodyBakedMesh = FRuntimeMorphBaker::BakeMorphs(OriginalMesh, BulkMatchSettings, CharacterCreation.MorphPresetData);
	//	BottomBody->SetSkeletalMesh(BottomBodyBakedMesh);
	//}
	//if (UpperBody)
	//{
	//	USkeletalMesh* OriginalMesh = GetUpperBodyMesh(CharacterCreation.UpperBodyId);
	//	USkeletalMesh* UpperBodyBakedMesh = FRuntimeMorphBaker::BakeMorphs(OriginalMesh, BulkMatchSettings, CharacterCreation.MorphPresetData);
	//	UpperBody->SetSkeletalMesh(UpperBodyBakedMesh);
	//}
}

void UCharacterCreationSubsystem::ApplyFromFromCharacterCreation(FCharacterCreation const& CharacterCreation, USkeletalMeshComponent* Head, USkeletalMeshComponent* BottomBody, USkeletalMeshComponent* UpperBody)
{
	if (Head && BottomBody && UpperBody)
	{
		//Head->SetSkeletalMesh(GetHeadMesh(CharacterCreation.HeadId));
		//BottomBody->SetSkeletalMesh(GetBottomBodyMesh(CharacterCreation.BottomBodyId));
		//UpperBody->SetSkeletalMesh(GetUpperBodyMesh(CharacterCreation.UpperBodyId));

		//Head->SetSkeletalMesh(GetHeadMesh(CharacterCreation.HeadId));
		//BottomBody->SetSkeletalMesh(GetBottomBodyMesh(CharacterCreation.BottomBodyId));
		//UpperBody->SetSkeletalMesh(GetUpperBodyMesh(CharacterCreation.UpperBodyId));


		for (int32 i = 0; i < CharacterCreation.SlotValues.Num(); i++)
		{
			if (CharacterCreation.SlotValues[i].Slot->Name.Contains(TEXT("Head")))
			{
				Head->SetSkeletalMesh(CharacterCreation.SlotValues[i].Value->Mesh);
			}
			else if (CharacterCreation.SlotValues[i].Slot->Name.Contains(TEXT("Upper")))
			{
				UpperBody->SetSkeletalMesh(CharacterCreation.SlotValues[i].Value->Mesh);
			}
			else if (CharacterCreation.SlotValues[i].Slot->Name.Contains(TEXT("Bottom")))
			{
				BottomBody->SetSkeletalMesh(CharacterCreation.SlotValues[i].Value->Mesh);
			}
		}


		for (const TPair<FName, FMorphPresetData>& PresetData : CharacterCreation.MorphPresetData)
		{
			Head->SetMorphTarget(PresetData.Value.MorphName, PresetData.Value.MorphWeight, true);
			BottomBody->SetMorphTarget(PresetData.Value.MorphName, PresetData.Value.MorphWeight, true);
			UpperBody->SetMorphTarget(PresetData.Value.MorphName, PresetData.Value.MorphWeight, true);
		}
	}
	else
	{
		UE_LOG(CharacterCreationLog, Error, TEXT("UCharacterCreationSubsystem::ApplyFromFromCharacterCreation: SkeletalMeshComponent or Preset was nullptr! Aborting"));
	}
}

void UCharacterCreationSubsystem::ApplyFromFromCharacterCreation(FCharacterCreation const& CharacterCreation, FCharacterCreationBodyParts const& BodyParts)
{
	ApplyFromFromCharacterCreation(CharacterCreation, BodyParts.Head, BodyParts.LowerBody, BodyParts.UpperBody);
}
