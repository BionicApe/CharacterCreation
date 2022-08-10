// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UI/AlertWidget.h"

#include "CharacterCreatorWidget.generated.h"

class UCharacterCreator;
class UListView;
class UHorizontalBox;
class UCCAttributesSetTabWidget;
class UWidgetSwitcher;
class UCCAttributesSetTabContentWidget;
class UCCMatAttSetTabContentWidget;
class UCCOutfitWidget;
class UCCGroomWidget;
class UCCBodyWidget;
class UCharacterCreatorModel;
class UButton;

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

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCAttributesSetTabWidget> TabButtonsWidgetClass;

	UPROPERTY(EditAnywhere, /*EditDefaultsOnly,*/ Category = Widgets)
	TSubclassOf<UCCOutfitWidget> OutfitWidgetClass;

	UPROPERTY(EditAnywhere, /*EditDefaultsOnly,*/ Category = Widgets)
	TSubclassOf<UCCGroomWidget> GroomWidgetClass;

	UPROPERTY(EditAnywhere, /*EditDefaultsOnly,*/ Category = Widgets)
	TSubclassOf<UCCBodyWidget> BodyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCAttributesSetTabContentWidget> TabContentWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UCCMatAttSetTabContentWidget> MaterialAttributeTabContentWidgetClass;

public:

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnBAWidgetClosed OnBAWidgetClosed;

public:
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void SetNewCharacterCreator(UCharacterCreator* NewCharacterCreator);
	
	void ReloadFromCharacterCreator();
	
	UFUNCTION()
	void OnTabSelected(UCCAttributesSetTabWidget* TabWidget, UWidget* TabContentWidget);

private:

	void CreateTab(FText TabText, UCCAttributesSetTabWidget* SelectedTabWidget, UWidget* SelectedContentWidget);

	UFUNCTION()
	void OnSaveButtonClicked();
};
