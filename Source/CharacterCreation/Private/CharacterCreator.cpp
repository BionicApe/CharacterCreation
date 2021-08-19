// Created by Bionic Ape. All Rights Reserved.


#include "CharacterCreator.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorOutfitsSet.h"
#include "CharacterCreatorAttributesSet.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorOutfitSlot.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


void UCharacterCreator::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterCreator, SlotAndOutfitArray);
	DOREPLIFETIME(UCharacterCreator, AttributeValues);
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

