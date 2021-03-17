// Created by Bionic Ape. All Rights Reserved.


#include "CharacterCreatorModel.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorOutfitsSet.h"
#include "CharacterCreatorAttributesSet.h"

//
//float UCharacterCreator::ValueOf(UCharacterCreatorAttribute* CCAttribute)
//{
//	if (FMorphPresetData* MorphData = CharacterCreation.MorphPresetData.Find(CCAttribute->MorphName))
//	{
//		return MorphData->MorphWeight;
//	}
//	return 0.f;
//}
//
//void UCharacterCreator::SetAttributeValue(UCharacterCreatorAttribute* CCAttribute, float NewValue)
//{
//	if (FMorphPresetData* MorphData = CharacterCreation.MorphPresetData.Find(CCAttribute->MorphName))
//	{
//		MorphData->MorphWeight = NewValue;
//	}
//}
//
//int32 UCharacterCreator::GetSelectedOutfitIndex(UCharacterCreatorOutfitsSet* CCOutfitSet)
//{
//	if (CCOutfitSet)
//	{
//
//		if (CCOutfitSet->OutfitsSetName == "Head")
//		{
//			return CharacterCreation.HeadId;
//		}
//		else if (CCOutfitSet->OutfitsSetName == "UpperBody")
//		{
//			return CharacterCreation.UpperBodyId;
//		}
//		else if (CCOutfitSet->OutfitsSetName == "BottomBody")
//		{
//			return CharacterCreation.BottomBodyId;
//		}
//	}
//	return -1;
//}
//
//UCharacterCreatorOutfit* UCharacterCreator::GetSelectedOutfit(UCharacterCreatorOutfitsSet* CCOutfitSet)
//{
//	if (CCOutfitSet)
//	{
//		for (UCharacterCreatorOutfitsSet* OutfitSetToCheck : OutfitSets)
//		{
//			if (OutfitSetToCheck->OutfitsSetName == CCOutfitSet->OutfitsSetName)
//			{
//				int32 Index = GetSelectedOutfitIndex(CCOutfitSet);
//				if (OutfitSetToCheck->Outfits.IsValidIndex(Index))
//				{
//					return OutfitSetToCheck->Outfits[Index];
//				}
//			}
//		}
//	}
//	return nullptr;
//}
//
//void UCharacterCreator::SetOutfit(UCharacterCreatorOutfitsSet* CCOutfitSet, int32 Index)
//{
//	if (CCOutfitSet)
//	{
//		if (CCOutfitSet->OutfitsSetName == "Head")
//		{
//			CharacterCreation.HeadId = (Index % CCOutfitSet->Outfits.Num());
//		}
//		else if (CCOutfitSet->OutfitsSetName == "UpperBody")
//		{
//			CharacterCreation.UpperBodyId = (Index % CCOutfitSet->Outfits.Num());
//		}
//		else if (CCOutfitSet->OutfitsSetName == "BottomBody")
//		{
//			CharacterCreation.BottomBodyId = (Index % CCOutfitSet->Outfits.Num());
//		}
//	}
//}
