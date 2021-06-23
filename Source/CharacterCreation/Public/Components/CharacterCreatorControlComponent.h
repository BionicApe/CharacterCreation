// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCreatorControlComponent.generated.h"

class UCharacterCreator;
class UCharacterCreatorAttribute;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERCREATION_API UCharacterCreatorControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<UCharacterCreator*> CharacterCreators;
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable)
	void AddCharacterCreator(UCharacterCreator* NewCharacterCreator);
	
	UFUNCTION(BlueprintCallable)
	void SetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetAttributeValue(UCharacterCreator* NewCharacterCreator, UCharacterCreatorAttribute* CCAttribute, float NewValue);
	
	UFUNCTION(BlueprintCallable)
	void SetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetOutfit(UCharacterCreator* CharacterCreator, UCharacterCreatorOutfit* SelectedOutfit);
};

