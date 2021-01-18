// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCreationTypes.h"
#include "CharacterCreatorComponent.generated.h"

class UCharacterCreator;
class USkeletalMeshComponent;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class CHARACTERCREATION_API UCharacterCreatorComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterCreator")
	UCharacterCreator* CharacterCreator;

	/**
	 * In case this character has a mesh that is not a character creator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	bool bCustomCharacter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	bool bLoadFromMain;

	UPROPERTY(ReplicatedUsing = "OnRep_CharacterCreation", EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	FCharacterCreation CharacterCreation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterCreator")
	FCharacterCreationBodyParts BodyPartsComponents;

public:

	UCharacterCreatorComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif // WITH_EDITOR

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnRep_CharacterCreation();

public:

	void ApplyNewCharacterCreator(FCharacterCreation const& NewCharacterCreation);

	void SetupBodyParts(USkeletalMeshComponent* Head, USkeletalMeshComponent* Bottom, USkeletalMeshComponent* Upper);

	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void LoadCharacterCreator(UCharacterCreator* NewCharacterCreator = nullptr);
	
	UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
	void SetCharacterCreator(UCharacterCreator* NewCharacterCreator);

};