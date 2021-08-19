// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CCOutfitListEntryWidget.generated.h"

class UTextBlock;
class UCharacterCreatorOutfitDH;
class UButton;

/**
 * 
 */
UCLASS()
class CHARACTERCREATIONUI_API UCCOutfitListEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* LeftButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RightButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameTextWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedOutfitName;

	UPROPERTY()
	UCharacterCreatorOutfitDH* CCOutfitDH;

public:

	virtual bool Initialize() override;

	bool IsListItemSelectable() const override { return CCOutfitDH != nullptr; }

	UFUNCTION()
	void OnLeftClicked();

	UFUNCTION()
	void OnRightClicked();

	void SetOutfit(bool bDirectionIsLeft);

protected:

	void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void UpdateOutfitText();
};