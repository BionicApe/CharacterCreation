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
#include "CharacterCreatorOutfitSlot.h"
#include "CharacterCreatorAttribute.h"
#include "Engine/ActorChannel.h"

UCharacterCreatorComponent::UCharacterCreatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	//OnSaveToDBDelegate.AddUObject(this, &UCharacterCreatorComponent::OnSaveDaoResponse);
	//OnLoadToDBDelegate.AddUObject(this, &UCharacterCreatorComponent::OnLoadDaoResponse);
	OnSaveToDBDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnSaveDaoResponse);
	OnLoadToDBDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnLoadDaoResponse);
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


	USkeletalMeshComponent* SkComp = SlotMeshMap.FindRef(Outfit->Slot);
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
	SkComp->SetSkeletalMesh(Outfit->Mesh);
	SlotMeshMap.Add(Outfit->Slot, SkComp);
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
		CCSubsystem->GetDao()->LoadCharacterCreator(DatabaseId, OnLoadToDBDelegate);
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
		CCSubsystem->GetDao()->SaveCharacterCreator(CharacterCreator, OnSaveToDBDelegate);
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
		//Destroy Meshes and empty SlotMeshMap, they aren't valid anymore
		for (auto SlotMes : SlotMeshMap)
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

		SlotMeshMap.Empty();

		if (CharacterCreatorLastUsed)
		{
			CharacterCreatorLastUsed->OnOutfitChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnOutfitChangedReceived);
			CharacterCreatorLastUsed->OnAttributeChangedDelegate.RemoveDynamic(this, &UCharacterCreatorComponent::OnAttributeChangedReceived);
		}

		if (CharacterCreator)
		{
			CharacterCreator->OnOutfitChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnOutfitChangedReceived);
			CharacterCreator->OnAttributeChangedDelegate.AddDynamic(this, &UCharacterCreatorComponent::OnAttributeChangedReceived);
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

		for (const FCCAttributeValue& AttributeValue : CharacterCreator->AttributeValues)
		{
			RootSkeletalMesh->SetMorphTarget(AttributeValue.Attribute->MorphName, AttributeValue.Value);
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

	if (RootSkeletalMesh && Attribute)
	{
		RootSkeletalMesh->SetMorphTarget(Attribute->MorphName, Value);
	}
}