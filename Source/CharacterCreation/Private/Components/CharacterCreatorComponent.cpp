// Created by Bionic Ape. All rights reseved.


#include "Components/CharacterCreatorComponent.h"
#include "Subsystems/CharacterCreationSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "CharacterCreator.h"
#include "CharacterCreationTypes.h"
#include "Net/UnrealNetwork.h"
#include "Interfaces/CharacterCreationDAO.h"
#include "CharacterCreatorOutfit.h"
#include "CharacterCreatorGroom.h"
#include "CharacterCreatorOutfitSlot.h"
#include "CharacterCreatorAttribute.h"
#include "CharacterCreatorMatAttribute.h"
#include "Engine/ActorChannel.h"
#include "GroomComponent.h"
#include "GroomBindingAsset.h"

UCharacterCreatorComponent::UCharacterCreatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	////OnSaveToDBDelegate.AddUObject(this, &UCharacterCreatorComponent::OnSaveDaoResponse);
	////OnLoadToDBDelegate.AddUObject(this, &UCharacterCreatorComponent::OnLoadDaoResponse);
	//OnSaveToDBDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnSaveDaoResponse);
	//OnLoadToDBDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnLoadDaoResponse);
}

void UCharacterCreatorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	ReloadCurrentCharacterCreator();
}

void UCharacterCreatorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(UCharacterCreatorComponent, BodyPartsComponents);//no need for it
	DOREPLIFETIME(UCharacterCreatorComponent, CharacterCreator);
}

bool UCharacterCreatorComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	WroteSomething |= Channel->ReplicateSubobject(CharacterCreator, *Bunch, *RepFlags);
	return WroteSomething;
}

void UCharacterCreatorComponent::OnRep_CharacterCreator()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	SetCharacterCreator(CharacterCreator);
}
void UCharacterCreatorComponent::SetCharacterCreator(UCharacterCreator* NewCharacterCreator)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	CharacterCreator = NewCharacterCreator;
	ReloadCurrentCharacterCreator();
}

void UCharacterCreatorComponent::SetOutfit(UCharacterCreatorOutfit* Outfit)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	USkeletalMeshComponent* SkComp = SlotSKMeshMap.FindRef(Outfit->Slot);
	if (!SkComp)
	{
		if (Outfit->Slot->bIsRoot)
		{
			SkComp = RootSkeletalMesh;
		}
		else
		{
			SkComp = NewObject<USkeletalMeshComponent>(GetOwner());
			SkComp->bUseAttachParentBound = true;
			SkComp->SetWorldTransform(FTransform::Identity);
			SkComp->AttachToComponent(RootSkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);
			SkComp->SetMasterPoseComponent(RootSkeletalMesh);
			SkComp->RegisterComponent();
		}
	}

	SkComp->SetSkeletalMesh(Outfit->Meshes[(uint8)CharacterCreator->BodyType]);
	SlotSKMeshMap.Add(Outfit->Slot, SkComp);
	SlotMeshMap.Add(Outfit->Slot, SkComp);
}

void UCharacterCreatorComponent::SetGroom(UCharacterCreatorGroom* NewGroom)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	UGroomComponent* GroomComp = SlotGroomMap.FindRef(NewGroom->Slot);

	if (!GroomComp)
	{

		GroomComp = NewObject<UGroomComponent>(GetOwner());
		GroomComp->SetWorldTransform(FTransform::Identity);
		//GroomComp->AttachToComponent(RootSkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);
		GroomComp->RegisterComponent();
	}

	////Bindig test for animation to work with grooms
	USkeletalMeshComponent* GroomAttachmentSKMeshComponent = Cast<USkeletalMeshComponent>(SlotMeshMap.FindRef(NewGroom->SlotToAttach));
	
	if (!GroomAttachmentSKMeshComponent) {
		return;
	}

	USkeletalMesh* BindingSlotToAttach = GroomAttachmentSKMeshComponent->SkeletalMesh;

	GroomComp->SetGroomAsset(NewGroom->GroomAsset);
	GroomComp->AttachToComponent(GroomAttachmentSKMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	NewGroom->Binding->TargetSkeletalMesh = BindingSlotToAttach; //This might change the asset for ALL character, TODO:Test and fix creating a copy of the asset for each character
	GroomComp->SetBinding(NewGroom->Binding);

	SlotGroomMap.Add(NewGroom->Slot, GroomComp);
	SlotMeshMap.Add(NewGroom->Slot, GroomComp);
}

bool UCharacterCreatorComponent::LoadCharacterCreatorFromDatabase()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	UCharacterCreationSubsystem* CCSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCharacterCreationSubsystem>();
	if (CCSubsystem->GetDao())
	{
		//CCSubsystem->GetDao()->LoadCharacterCreator(DatabaseId, OnLoadToDBDelegate);
		return true;
	}
	return false;
}

bool UCharacterCreatorComponent::SaveCharacterCreatorToDatabase()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	UCharacterCreationSubsystem* CCSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCharacterCreationSubsystem>();
	if (CCSubsystem->GetDao())
	{
		//CCSubsystem->GetDao()->SaveCharacterCreator(CharacterCreator, OnSaveToDBDelegate);
		return true;
	}
	return false;
}

void UCharacterCreatorComponent::OnSaveDaoResponse(FAsyncCharacterCreatorResponse Response)
{
	if (Response.bIsSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorComponent::OnSaveDaoResponse Succesfully saved."))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UCharacterCreatorComponent::OnSaveDaoResponse error: %s"), *Response.ErrorMessage)
	}
}

void UCharacterCreatorComponent::OnLoadDaoResponse(FAsyncCharacterCreatorResponse Response)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	if (Response.bIsSuccessful)
	{
		SetCharacterCreator(Response.CharacterCreator);
		UE_LOG(LogTemp, Log, TEXT("UCharacterCreatorComponent::OnLoadDaoResponse Succesfully Loaded."))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UCharacterCreatorComponent::OnLoadDaoResponse error: %s"), *Response.ErrorMessage)
	}
}

void UCharacterCreatorComponent::OnChangedReceived()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	//ReloadCurrentCharacterCreator();

	//if (GetOwner()->GetLocalRole() == ROLE_Authority)
	//{
	//	SaveCharacterCreatorToDatabase();
	//}
}

void UCharacterCreatorComponent::ReloadCurrentCharacterCreator()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	bool bAreDifferent = CharacterCreator != CharacterCreatorLastUsed;

	if (bAreDifferent)
	{
		//Destroy Meshes and empty SlotSKMeshMap, they aren't valid anymore
		for (auto SlotMes : SlotSKMeshMap)
		{
			if (SlotMes.Key->bIsRoot)
			{
				SlotMes.Value->SetSkeletalMesh(nullptr);
			}
			else
			{
				SlotMes.Value->DestroyComponent(false);
			}
		}

		SlotSKMeshMap.Empty();

		//Destroy Grooms and empty SlotGroomMap, they aren't valid anymore
		for (auto SlotGroom : SlotGroomMap)
		{
			SlotGroom.Value->DestroyComponent(false);
		}

		SlotGroomMap.Empty();

		SlotMeshMap.Empty();

		if (CharacterCreatorLastUsed)
		{
			CharacterCreatorLastUsed->OnOutfitChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnOutfitChangedReceived);
			CharacterCreatorLastUsed->OnGroomChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnGroomChangedReceived);

			CharacterCreatorLastUsed->OnAttributeChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnAttributeChangedReceived);
			CharacterCreatorLastUsed->OnMaterialAttributeChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnMaterialAttributeChangedReceived);

			CharacterCreatorLastUsed->OnBodyTypeChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnBodyTypeChangedReceived);
		}

		if (CharacterCreator)
		{
			CharacterCreator->OnOutfitChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnOutfitChangedReceived);
			CharacterCreator->OnGroomChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnGroomChangedReceived);

			CharacterCreator->OnAttributeChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnAttributeChangedReceived);
			CharacterCreator->OnMaterialAttributeChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnMaterialAttributeChangedReceived);
			
			CharacterCreator->OnBodyTypeChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnBodyTypeChangedReceived);
		}
	}

	CharacterCreatorLastUsed = CharacterCreator;//This is crucial to keep track of the generation

	if (CharacterCreator)
	{
		//I assign all outfits regardless of they are different or not
		for (const FCCSlotAndOutfit& SlotAndOutfit : CharacterCreator->SlotAndOutfitArray)
		{
			SetOutfit(SlotAndOutfit.Outfit);
		}

		for (const FCCSlotAndGroom& SlotAndGroom : CharacterCreator->SlotAndGroomArray)
		{
			SetGroom(SlotAndGroom.Groom);
		}

		for (const FCCAttributeValue& AttributeValue : CharacterCreator->AttributeValues)
		{
			SetMorphTarget(AttributeValue.Attribute,AttributeValue.Value);
		}

		//Set material attributes for relevant slots
		for (const FCCMaterialAttributeValue& AttributeValue : CharacterCreator->MaterialAttributeValues)
		{
			UCharacterCreatorOutfitSlot* Slot = AttributeValue.MaterialAttribute->TargetSlot;
			UMeshComponent* Mesh = SlotMeshMap.FindRef(Slot);

			if (Mesh && AttributeValue.MaterialAttribute)
			{
				Mesh->SetScalarParameterValueOnMaterials(AttributeValue.MaterialAttribute->ScalarParameterName, AttributeValue.Value);
			}

			for (uint8 i = 0; i < AttributeValue.AffectedSlots.Num(); ++i)
			{
				Slot = AttributeValue.AffectedSlots[i];
				Mesh = SlotMeshMap.FindRef(Slot);

				Mesh->SetScalarParameterValueOnMaterials(AttributeValue.MaterialAttribute->ScalarParameterName, AttributeValue.Value);
			}
		}
	}
}

void UCharacterCreatorComponent::OnOutfitChangedReceived(UCharacterCreatorOutfit* Outfit)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	SetOutfit(Outfit);
}

void UCharacterCreatorComponent::OnGroomChangedReceived(UCharacterCreatorGroom* Groom)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	SetGroom(Groom);
}


void UCharacterCreatorComponent::OnAttributeChangedReceived(UCharacterCreatorAttribute* Attribute, float Value)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}
	SetMorphTarget(Attribute, Value);
}

void UCharacterCreatorComponent::SetMorphTarget(const UCharacterCreatorAttribute* Attribute, const float& Value)
{
	if (RootSkeletalMesh && Attribute && RootSkeletalMesh->FindMorphTarget(Attribute->MorphName))
	{
		RootSkeletalMesh->SetMorphTarget(Attribute->MorphName, Value);
	}
}
void UCharacterCreatorComponent::OnMaterialAttributeChangedReceived(UCharacterCreatorMatAttribute* MaterialAttribute, float Value)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	if (MaterialAttribute)
	{
		for (FCCMaterialAttributeValue& AttributeValue : CharacterCreator->MaterialAttributeValues)
		{
			if (AttributeValue.MaterialAttribute == MaterialAttribute)
			{
				UCharacterCreatorOutfitSlot* Slot = AttributeValue.MaterialAttribute->TargetSlot;
				UMeshComponent* Mesh = SlotMeshMap.FindRef(Slot);

				if (Mesh)
				{
					Mesh->SetScalarParameterValueOnMaterials(MaterialAttribute->ScalarParameterName, Value);
				}

				for (uint8 i = 0; i < AttributeValue.AffectedSlots.Num(); ++i)
				{
					Slot = AttributeValue.AffectedSlots[i];
					Mesh = SlotMeshMap.FindRef(Slot);

					Mesh->SetScalarParameterValueOnMaterials(MaterialAttribute->ScalarParameterName, Value);
				}

				break;
			}
		}

	}
}

void UCharacterCreatorComponent::OnBodyTypeChangedReceived(FCharacterCreationBodyType NewBodyType)
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I'm Client"));
	}

	CharacterCreator->BodyType = NewBodyType;
	
	for (const FCCSlotAndOutfit& SlotAndOutfit : CharacterCreator->SlotAndOutfitArray)
	{
		SetOutfit(SlotAndOutfit.Outfit);
	}
}

