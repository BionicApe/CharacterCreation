// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreationSubsystem.generated.h"

class UDataTable;
class USkeletalMesh;
class UCharacterCreatorOutfitsSet;

DECLARE_LOG_CATEGORY_EXTERN(CharacterCreationLog, Warning, All);

/**
 * 
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	FCharacterCreation MainCharacterCreation;

public:

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	//UDataTable* CharacterCreations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UDataTable* HeadMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UDataTable* UpperBodyMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UDataTable* BottomBodyMeshes;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UCharacterCreatorOutfitsSet* HeadOutfits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UCharacterCreatorOutfitsSet* UpperBodyOutfits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UCharacterCreatorOutfitsSet* BottomBodyOutfits;

public:

	UCharacterCreationSubsystem();

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	USkeletalMesh* CreateSkeletalMesh(FCharacterCreation const& CharacterCreation);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	USkeletalMesh* GetHeadMesh(int32 id);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	USkeletalMesh* GetBottomBodyMesh(int32 id);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	USkeletalMesh* GetUpperBodyMesh(int32 id);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SetFromCharacterCreation(FCharacterCreation const& CharacterCreation, USkeletalMeshComponent* Head, USkeletalMeshComponent* BottomBody, USkeletalMeshComponent* UpperBody);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void ApplyFromFromCharacterCreation(FCharacterCreation const& CharacterCreation, USkeletalMeshComponent* Head, USkeletalMeshComponent* BottomBody, USkeletalMeshComponent* UpperBody);
	void ApplyFromFromCharacterCreation(FCharacterCreation const& CharacterCreation, FCharacterCreationBodyParts const& BodyParts);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SaveMainCharacterCreation(FCharacterCreation NewMainCharacterCreation) 
	{ 
		MainCharacterCreation = NewMainCharacterCreation;
	}
};
