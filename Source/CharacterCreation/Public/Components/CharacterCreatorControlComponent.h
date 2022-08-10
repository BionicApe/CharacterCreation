// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControlComponent.h"
#include "Interfaces/CharacterCreationDAO.h"
#include "CharacterCreatorControlComponent.generated.h"

class UCharacterCreator;
class UCharacterCreatorAttribute;
class UCharacterCreatorMatAttribute;
//class UCharacterCreatorSlotDH;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCCMatAttAffectedSlotsChanged, UCharacterCreatorSlotDH*, OtherCCSlotDH, bool, NewValue);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERCREATION_API UCharacterCreatorControlComponent : public UControlComponent
{
	GENERATED_BODY()

public:	

	//FOnCCMatAttAffectedSlotsChanged OnCCMatAttAffectedSlotsChanged;

	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<UCharacterCreator*> CharacterCreators;

	UPROPERTY(VisibleAnywhere, Replicated)
	UCharacterCreator* MainCharacterCreator;
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable)
	void AddCharacterCreator(UCharacterCreator* NewCharacterCreator, bool bIsMainCC = true);
	
	UFUNCTION(BlueprintCallable)
	void SetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue);

	//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
	UFUNCTION(BlueprintCallable)
	void SetMaterialAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, float NewValue);

	//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaterialAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, float NewValue);
	
	UFUNCTION(BlueprintCallable)
	void SetMaterialAttributeAffectedSlots(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool NewValue);

	/*UFUNCTION(BlueprintCallable)
	void SetMaterialAttributeAffectedSlots(UCharacterCreatorSlotDH* CCSlotDH, bool NewValue);*/

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaterialAttributeAffectedSlots(UCharacterCreator* NewCharacterCreator, UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool NewValue);

	UFUNCTION(BlueprintCallable)
	void SetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit);

	UFUNCTION(BlueprintCallable)
	void SetGroom(UCharacterCreator* CharacterCreator, UCharacterCreatorGroom* SelectedGroom);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetGroom(UCharacterCreator* CharacterCreator, UCharacterCreatorGroom* SelectedGroom);

	UFUNCTION(BlueprintCallable)
	void SetBodyType(UCharacterCreator* CharacterCreator, FCharacterCreationBodyType NewBodyType);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetBodyType(UCharacterCreator* CharacterCreator, FCharacterCreationBodyType NewBodyType);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SaveCharacterCreator(UCharacterCreator* CharacterCreator);

	UFUNCTION()
	void OnDaoResponse(FAsyncCharacterCreatorResponse Response);
};

