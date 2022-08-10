// Created by Bionic Ape. All Rights Reserved.


#include "CharacterCreator.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorMatAttribute.h"
#include "CharacterCreatorOutfitsSet.h"
#include "CharacterCreatorAttributesSet.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorGroom.h"
#include "CharacterCreatorOutfitSlot.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


void UCharacterCreator::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreator, SlotAndOutfitArray);
	DOREPLIFETIME(UCharacterCreator, SlotAndGroomArray);
	DOREPLIFETIME(UCharacterCreator, AttributeValues);
	DOREPLIFETIME(UCharacterCreator, MaterialAttributeValues);
	DOREPLIFETIME(UCharacterCreator, MaterialAttributeValues);
	DOREPLIFETIME(UCharacterCreator, BodyType);
	DOREPLIFETIME(UCharacterCreator, Model);
}

int32 UCharacterCreator::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	if (HasAnyFlags(RF_ClassDefaultObject) || !IsSupportedForNetworking())
	{
		// This handles absorbing authority/cosmetic
		return GEngine->GetGlobalFunctionCallspace(Function, this, Stack);
	}
	check(GetOuter() != nullptr);
	return GetOuter()->GetFunctionCallspace(Function, Stack);
}

bool UCharacterCreator::CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack)
{
	check(!HasAnyFlags(RF_ClassDefaultObject));
	check(GetOuter() != nullptr);

	AActor* Owner = CastChecked<AActor>(GetOuter());

	bool bProcessed = false;

	FWorldContext* const Context = GEngine->GetWorldContextFromWorld(GetWorld());
	if (Context != nullptr)
	{
		for (FNamedNetDriver& Driver : Context->ActiveNetDrivers)
		{
			if (Driver.NetDriver != nullptr && Driver.NetDriver->ShouldReplicateFunction(Owner, Function))
			{
				Driver.NetDriver->ProcessRemoteFunction(Owner, Function, Parameters, OutParms, Stack, this);
				bProcessed = true;
			}
		}
	}
	return bProcessed;
}

UWorld* UCharacterCreator::GetWorld() const
{
	if (HasAllFlags(RF_ClassDefaultObject))
	{
		// If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
		return nullptr;
	}
	return GetOuter()->GetWorld();
}

float UCharacterCreator::ValueOf(UCharacterCreatorAttribute* CCAttribute)
{
	for (FCCAttributeValue AttributeValue : AttributeValues)
	{
		if (AttributeValue.Attribute == CCAttribute)
		{
			return AttributeValue.Value;
		}
	}
	return 0.f;
}

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
float UCharacterCreator::ValueOf(UCharacterCreatorMatAttribute* CCAttribute)
{
	for (FCCMaterialAttributeValue MaterialAttributeValue : MaterialAttributeValues)
	{
		if (MaterialAttributeValue.MaterialAttribute == CCAttribute)
		{
			return MaterialAttributeValue.Value;
		}
	}
	return 0.f;
}

TArray<UCharacterCreatorOutfitSlot*> UCharacterCreator::AffectedSlotsOf(UCharacterCreatorMatAttribute* CCAttribute)
{
	TArray<UCharacterCreatorOutfitSlot*> RetrievedAffectedSlotsArray;
	for (FCCMaterialAttributeValue MaterialAttributeValue : MaterialAttributeValues)
	{
		if (MaterialAttributeValue.MaterialAttribute == CCAttribute)
		{
			RetrievedAffectedSlotsArray = MaterialAttributeValue.AffectedSlots;
		}
	}
	return RetrievedAffectedSlotsArray;
}

void UCharacterCreator::SetAttributeValue(UCharacterCreatorAttribute* CCAttribute, float NewValue)
{
	bool bIsFound = false;

	for (FCCAttributeValue& AttributeValue : AttributeValues)
	{
		if (AttributeValue.Attribute == CCAttribute)
		{
			AttributeValue.Value = NewValue;
			bIsFound = true;
			break;
		}
	}
	if (!bIsFound)
	{
		AttributeValues.Emplace(CCAttribute, NewValue);//We create a new entry otherwise
	}

	Multicast_AttributeChanged(CCAttribute, NewValue);
}

void UCharacterCreator::Multicast_AttributeChanged_Implementation(UCharacterCreatorAttribute* Attribute, float NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("UCharacterCreator::Multicast_AttributeChanged_Implementation() Called, Attribute: %s and Value: %f"), *Attribute->GetName(), NewValue);

	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	OnAttributeChangedDelegate.Broadcast(Attribute, NewValue);
}

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
void UCharacterCreator::SetMaterialAttributeValue(UCharacterCreatorMatAttribute* CCAttribute, float NewValue)
{
	bool bIsFound = false;

	for (FCCMaterialAttributeValue& AttributeValue : MaterialAttributeValues)
	{
		if (AttributeValue.MaterialAttribute == CCAttribute)
		{
			AttributeValue.Value = NewValue;
			bIsFound = true;

			break;
		}
	}
	if (!bIsFound)
	{
		MaterialAttributeValues.Emplace(CCAttribute, NewValue);//We create a new entry otherwise
	}

	Multicast_MaterialAttributeChanged(CCAttribute, NewValue);
}

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
void UCharacterCreator::Multicast_MaterialAttributeChanged_Implementation(UCharacterCreatorMatAttribute* MaterialAttribute, float NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("UCharacterCreator::Multicast_AttributeChanged_Implementation() Called, Attribute: %s and Value: %f"), *MaterialAttribute->GetName(), NewValue);

	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	OnMaterialAttributeChangedDelegate.Broadcast(MaterialAttribute, NewValue);
}

//TODO: Change to separate functions, add and remove, as this functionality is redundant when sharing slot with other MaterialAttributes
void UCharacterCreator::SetMaterialAttributeAffectedSlots(UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool bIsChecked)
{
	for (FCCMaterialAttributeValue& AttributeValue : MaterialAttributeValues)
	{
		if (AttributeValue.MaterialAttribute == CCAttribute)
		{
			//SetMaterialAttributeAffectedSlots(AttributeValue.MaterialAttribute, 
			if (bIsChecked) 
			{
				//This condition should never be true, the statement is just for security
				if (!AttributeValue.AffectedSlots.Contains(Slot)) 
				{
					AttributeValue.AffectedSlots.Emplace(Slot);
					
					for (FCCMaterialAttributeValue& SharedSlotAttributeValue : MaterialAttributeValues)
					{
						if (SharedSlotAttributeValue.MaterialAttribute->TargetSlot == Slot)
						{
							SetMaterialAttributeAffectedSlots(SharedSlotAttributeValue.MaterialAttribute, AttributeValue.MaterialAttribute->TargetSlot, bIsChecked);
						}
					}
				}
			}
			else 
			{
				//This condition should never be true, the statement is just for security
				if (AttributeValue.AffectedSlots.Contains(Slot)) 
				{
					AttributeValue.AffectedSlots.Remove(Slot);

					for (FCCMaterialAttributeValue& SharedSlotAttributeValue : MaterialAttributeValues)
					{
						if (SharedSlotAttributeValue.MaterialAttribute->TargetSlot == Slot)
						{
							SetMaterialAttributeAffectedSlots(SharedSlotAttributeValue.MaterialAttribute, AttributeValue.MaterialAttribute->TargetSlot, bIsChecked);
						}
					}
				}
			}

			break;
		}
	}

	Multicast_MaterialAttributeChanged(CCAttribute, bIsChecked);
}

//Quick fix for material attribute testing, TODO:Interface/Hierarchy the attributes so they share types
void UCharacterCreator::Multicast_MaterialAttributeAffectedSlotChanged_Implementation(UCharacterCreatorMatAttribute* CCAttribute, UCharacterCreatorOutfitSlot* Slot, bool NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("UCharacterCreator::Multicast_MaterialAttributeAffectedSlotChanged_Implementation() Called, Attribute: %s and Value: %f"), *CCAttribute->GetName(), NewValue);

	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	//OnMaterialAttributeChangedDelegate.Broadcast(MaterialAttribute, NewValue);
}

UCharacterCreatorOutfit* UCharacterCreator::GetSelectedOutfit(UCharacterCreatorOutfitSlot* Slot)
{
	for (FCCSlotAndOutfit& SlotAndOutfit : SlotAndOutfitArray)
	{
		if (SlotAndOutfit.Slot == Slot)
		{
			return SlotAndOutfit.Outfit;
		}
	}
	return nullptr;
}

void UCharacterCreator::SetOutfit(UCharacterCreatorOutfit* Outfit)
{
	bool bIsFound = false;
	if (Outfit && Outfit->Slot)
	{
		for (FCCSlotAndOutfit& SlotAndOutfit : SlotAndOutfitArray)
		{
			if (SlotAndOutfit.Slot == Outfit->Slot)
			{
				SlotAndOutfit.Outfit = Outfit;
				bIsFound = true;
				break;
			}
		}
	}
	if (!bIsFound)
	{
		SlotAndOutfitArray.Emplace(Outfit->Slot, Outfit);//We create a new entry otherwise
	}
	Multicast_OutfitChanged(Outfit);
}

void UCharacterCreator::Multicast_OutfitChanged_Implementation(UCharacterCreatorOutfit* Outfit)
{
	OnOutfitChangedDelegate.Broadcast(Outfit);
}



UCharacterCreatorGroom* UCharacterCreator::GetSelectedGroom(UCharacterCreatorOutfitSlot* Slot)
{
	for (FCCSlotAndGroom& SlotAndGroom : SlotAndGroomArray)
	{
		if (SlotAndGroom.Slot == Slot)
		{
			return SlotAndGroom.Groom;
		}
	}
	return nullptr;
}

void UCharacterCreator::SetGroom(UCharacterCreatorGroom* Groom)
{
	bool bIsFound = false;
	if (Groom && Groom->Slot)
	{
		for (FCCSlotAndGroom& SlotAndGroom : SlotAndGroomArray)
		{
			if (SlotAndGroom.Slot == Groom->Slot)
			{
				SlotAndGroom.Groom = Groom;
				bIsFound = true;
				break;
			}
		}
	}
	if (!bIsFound)
	{
		SlotAndGroomArray.Emplace(Groom->Slot, Groom);//We create a new entry otherwise
	}
	Multicast_GroomChanged(Groom);
}

void UCharacterCreator::Multicast_GroomChanged_Implementation(UCharacterCreatorGroom* Groom)
{
	OnGroomChangedDelegate.Broadcast(Groom);
}


FCharacterCreationBodyType UCharacterCreator::GetSelectedBodyType() 
{
	return BodyType;
}

void UCharacterCreator::SetBodyType(FCharacterCreationBodyType NewBodyType)
{
	BodyType = NewBodyType;
	Multicast_BodyTypeChanged(NewBodyType);
}

void UCharacterCreator::Multicast_BodyTypeChanged_Implementation(FCharacterCreationBodyType NewBodyType) 
{
	OnBodyTypeChangedDelegate.Broadcast(NewBodyType);
}