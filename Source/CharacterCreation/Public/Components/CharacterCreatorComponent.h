// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCreationTypes.h"
#include "Interfaces/CharacterCreationDAO.h"
#include "CharacterCreatorComponent.generated.h"

class UCharacterCreator;
class USkeletalMeshComponent;
class UGroomComponent;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	//UPROPERTY(ReplicatedUsing="OnRep_CharacterCreator", EditAnywhere, BlueprintReadOnly, Category = "CharacterCreator")
	UPROPERTY(ReplicatedUsing = "OnRep_CharacterCreator", EditAnywhere, BlueprintReadOnly, Category = "CharacterCreator")
	UCharacterCreator* CharacterCreator;

	/**
	 * It's used for clients so it's not overriden by Server
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterCreator")
	UCharacterCreator* CharacterCreatorLastUsed;

	UPROPERTY(Transient)
	TMap<UCharacterCreatorOutfitSlot*, USkeletalMeshComponent*> SlotSKMeshMap;

	UPROPERTY(Transient)
	TMap<UCharacterCreatorOutfitSlot*, UGroomComponent*> SlotGroomMap;

	//Slot mesh map contains duplicated data as it is a concatenation of slots and grooms used to share material attributes
	UPROPERTY(Transient)
	TMap<UCharacterCreatorOutfitSlot*, UMeshComponent*> SlotMeshMap;

public:

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	USkeletalMeshComponent* RootSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	int32 DatabaseId;

	/**
	 * In case this character has a mesh that is not a character creator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	bool bCustomCharacter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	bool bLoadFromMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	FCharacterCreationBodyParts BodyPartsComponents;

	UPROPERTY(BlueprintAssignable, Category = "CharacterCreator")
	FAsyncSaveCharacterCreatorDelegate OnSaveToDBDelegate;

	UPROPERTY(BlueprintAssignable, Category = "CharacterCreator")
	FAsyncLoadCharacterCreatorDelegate OnLoadToDBDelegate;


public:

	UCharacterCreatorComponent();

	UCharacterCreator* GetCharacterCreator() const { return CharacterCreator; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnRep_CharacterCreator();
	
	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SetCharacterCreator(UCharacterCreator* NewCharacterCreator);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SetOutfit(UCharacterCreatorOutfit* NewOutfit);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SetGroom(UCharacterCreatorGroom* NewGroom);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	bool LoadCharacterCreatorFromDatabase();

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	bool SaveCharacterCreatorToDatabase();

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void OnSaveDaoResponse(FAsyncCharacterCreatorResponse Response);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void OnLoadDaoResponse(FAsyncCharacterCreatorResponse Response);
	
	UFUNCTION()
	void OnChangedReceived();
	
	UFUNCTION()
	void ReloadCurrentCharacterCreator();
	
	UFUNCTION()
	void OnOutfitChangedReceived(UCharacterCreatorOutfit* Outfit);

	UFUNCTION()
	void OnGroomChangedReceived(UCharacterCreatorGroom* Groom);
	
	UFUNCTION()
	void OnAttributeChangedReceived(UCharacterCreatorAttribute* Attribute, float Value);

	UFUNCTION()
	void SetMorphTarget(const UCharacterCreatorAttribute* Attribute, const float& Value);	
	
	UFUNCTION()
	void OnMaterialAttributeChangedReceived(UCharacterCreatorMatAttribute* MaterialAttribute, float Value);

	UFUNCTION()
	void OnBodyTypeChangedReceived(FCharacterCreationBodyType NewBodyType);
};