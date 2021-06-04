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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterCreatorChanged);

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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	TArray<FCCSlotAndOutfit> SlotAndOutfitArray;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterCreator)
	TArray<FCCAttributeValue> AttributeValues;

	UPROPERTY(Replicated)
	FOnCharacterCreatorChanged OnChanged;
		
public:
	

	float ValueOf(UCharacterCreatorAttribute* CCAttribute);
	void SetAttributeValue(UCharacterCreatorAttribute* Attribute, float NewValue);
	UFUNCTION(Server, Reliable)
	void ServerSetAttributeValue(UCharacterCreatorAttribute* Attribute, float NewValue);

	UCharacterCreatorOutfit* GetSelectedOutfit(UCharacterCreatorOutfitSlot* OutfitSlot);
	void SetOutfit(UCharacterCreatorOutfit* Outfit);
	UFUNCTION(Server, Reliable)
	void ServerSetOutfit(UCharacterCreatorOutfit* Outfit);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnChanged();

	virtual bool IsSupportedForNetworking() const override { return true; }
	//virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags); // note no override because this is the FIRST declaration of this function.
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

};
