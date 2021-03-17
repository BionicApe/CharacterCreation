// Created by Bionic Ape. All Rights Reserved.

#include "Factories/CharacterCreatorOutfitFactory.h"
#include "CharacterCreatorOutfit.h"

UCharacterCreatorOutfitFactory::UCharacterCreatorOutfitFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SupportedClass = UCharacterCreatorOutfit::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UCharacterCreatorOutfitFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	UCharacterCreatorOutfit* NewAsset = NewObject<UCharacterCreatorOutfit>(InParent, Class, Name, Flags);
	return NewAsset;
}