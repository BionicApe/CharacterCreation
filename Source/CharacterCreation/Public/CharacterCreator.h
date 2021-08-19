// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreator.generated.h"

class UCharacterCreatorAttributesSet;
class UCharacterCreatorAttribute;
class UCharacterCreatorOutfit;
class UCharacterCreatorOutfitSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterCreatorOutfitChanged, UCharacterCreatorOutfit*, Outfit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterCreatorAttributeChanged, UCharacterCreatorAttribute*, Attribute, float, Value);

/**
 *
 */
UCLASS()
class CHARACTERCREATION_API UCharacterCreator : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 DatabaseId;

	UPROPERTY(VisibleAnywhere)
	FString Id;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	TArray<FCCSlotAndOutfit> SlotAndOutfitArray;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	TArray<FCCAttributeValue> AttributeValues;

	UPROPERTY(Transient)
	FOnCharacterCreatorOutfitChanged OnOutfitChangedDelegate;

	UPROPERTY(Transient)
	FOnCharacterCreatorAttributeChanged OnAttributeChangedDelegate;

public:

	FORCEINLINE AActor* GetOwningActor() const { return Cast<AActor>(GetOuter()); }

	FORCEINLINE UActorComponent* GetOwningComponent() const { return Cast<UActorComponent>(GetOuter()); }

	//Functions Needed to replicate, from UObject
	virtual bool IsSupportedForNetworking() const override { return true; }
	//virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags); // note no override because this is the FIRST declaration of this function.
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;
	virtual UWorld* GetWorld() const override;
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	//End Functions Needed to replicate, from UObject

	float ValueOf(UCharacterCreatorAttribute* CCAttribute);
	void SetAttributeValue(UCharacterCreatorAttribute* Attribute, float NewValue);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AttributeChanged(UCharacterCreatorAttribute* Attribute, float NewValue);

	UCharacterCreatorOutfit* GetSelectedOutfit(UCharacterCreatorOutfitSlot* OutfitSlot);
	void SetOutfit(UCharacterCreatorOutfit* Outfit);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OutfitChanged(UCharacterCreatorOutfit* Outfit);

	// Overrides
	/*
	virtual bool IsNameStableForNetworking() const override;
	virtual void PreNetReceive() override;
	virtual void PostNetReceive() override;*/

	//UFUNCTION()
	//void OnRepSlotAndOutfitArray();
	//


};
