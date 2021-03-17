// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CCAttributesSetTabContentWidget.generated.h"

class UCharacterCreatorAttributesSet;
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
	TArray<UCharacterCreatorAttributeDH*> DataHolderArray;

public:
	
	virtual bool Initialize() override;

	virtual void SetAttributesSet(UCharacterCreatorAttributesSet* NewAttributesSet, UCharacterCreator* NewCharacterCrator);
};
