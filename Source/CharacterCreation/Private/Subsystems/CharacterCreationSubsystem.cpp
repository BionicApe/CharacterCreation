// Created by Bionic Ape. All Rights Reserved.


#include "Subsystems/CharacterCreationSubsystem.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

static const FString ContextString(TEXT("Character Creation"));
DEFINE_LOG_CATEGORY(CharacterCreationLog);


UCharacterCreationSubsystem::UCharacterCreationSubsystem() : Super()
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> CharacterCreationsDT(TEXT("DataTable'/Game/ThePrison/Data/DT_CharacterCreations.DT_CharacterCreations'"));
	//CharacterCreations = CharacterCreationsDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> HeadMeshesDT(TEXT("DataTable'/Game/CharacterCreation/DT_CCHeadMeshes.DT_CCHeadMeshes'"));
	HeadMeshes = HeadMeshesDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> UpperBodyMeshesDT(TEXT("DataTable'/Game/CharacterCreation/DT_CCUpperBodyMeshes.DT_CCUpperBodyMeshes'"));
	UpperBodyMeshes = UpperBodyMeshesDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> BottomBodyMeshesDT(TEXT("DataTable'/Game/CharacterCreation/DT_CCBottomBodyMeshes.DT_CCBottomBodyMeshes'"));
	BottomBodyMeshes = BottomBodyMeshesDT.Object;
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
	FCharacterCreationMesh* Row = HeadMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	if (Row)
	{
		return Row->Mesh;
	}
	return nullptr;
}

USkeletalMesh* UCharacterCreationSubsystem::GetBottomBodyMesh(int32 id)
{
	FCharacterCreationMesh* Row = BottomBodyMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	if (Row)
	{
		return Row->Mesh;
	}
	return nullptr;
}

USkeletalMesh* UCharacterCreationSubsystem::GetUpperBodyMesh(int32 id)
{
	FCharacterCreationMesh* Row = UpperBodyMeshes->FindRow<FCharacterCreationMesh>(FName(*FString::FromInt(id)), ContextString, true);
	if (Row)
	{
		return Row->Mesh;
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
		Head->SetSkeletalMesh(GetHeadMesh(CharacterCreation.HeadId));
		BottomBody->SetSkeletalMesh(GetBottomBodyMesh(CharacterCreation.BottomBodyId));
		UpperBody->SetSkeletalMesh(GetUpperBodyMesh(CharacterCreation.UpperBodyId));

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
