// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterCreationHUD.generated.h"

class UCharacterCreatorWidget;
class UCharacterCreator;

/**
 * 
 */
UCLASS()
class CHARACTERCREATIONUI_API ACharacterCreationHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCharacterCreatorWidget> CCWidgetClass;
	UPROPERTY(Transient, BlueprintReadOnly, Category = Widgets)
	UCharacterCreatorWidget* CCWidget;

protected:
	
	virtual void BeginPlay() override;

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void CreateCCWidget(UCharacterCreator* CharacterCreator);
};
