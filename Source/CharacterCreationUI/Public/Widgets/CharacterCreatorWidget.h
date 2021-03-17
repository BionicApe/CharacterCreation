// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCreatorWidget.generated.h"

class UCharacterCreator;
class UListView;
class UHorizontalBox;
class UCCAttributesSetTabWidget;
class UWidgetSwitcher;
class UCCAttributesSetTabContentWidget;
class UCCOutfitWidget;
class UCharacterCreatorModel;

/**
 * 
 */
UCLASS()
class CHARACTERCREATIONUI_API UCharacterCreatorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	UCharacterCreator* CharacterCreator;

	UPROPERTY(EditAnywhere)
	UCharacterCreatorModel* CharacterCreatorModel;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* AttributesTabs;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* AttributesSetSwitcher;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCAttributesSetTabWidget> TabButtonsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCOutfitWidget> OutfitWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCAttributesSetTabContentWidget> TabContentWidgetClass;

public:
	
	virtual bool Initialize() override;
	
	void SetCharacterCreator(UCharacterCreator* CharacterCreator);
	
	void ReloadFromCharacterCreator();
	
	UFUNCTION()
	void OnTabSelected(UCCAttributesSetTabWidget* TabWidget, UWidget* TabContentWidget);

private:

	void CreateTab(FText TabText, UCCAttributesSetTabWidget* SelectedTabWidget, UWidget* SelectedContentWidget);
};
