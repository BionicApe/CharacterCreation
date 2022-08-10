// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CCAttributesSetTabContentWidget.generated.h"

class UCharacterCreatorAttributesSet;
class UCharacterCreatorMatAttributesSet;
class UCharacterCreator;
class UListView;
class UCharacterCreatorAttributeDH;


/**
 * 
 */
UCLASS()
class CHARACTERCREATIONUI_API UCCAttributesSetTabContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UListView* AttributeListView;

	UPROPERTY()
	UCharacterCreatorAttributesSet* AttributesSet;

	UPROPERTY()
	UCharacterCreator* CharacterCreator;

	UPROPERTY()
	TArray<UCharacterCreatorAttributeDH*> AttributesDataHolderArray;

public:
	
	virtual bool Initialize() override;

	virtual void SetAttributesSet(UCharacterCreatorAttributesSet* NewAttributesSet, UCharacterCreator* NewCharacterCreator);
};
