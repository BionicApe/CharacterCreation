// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "SCCWorkbenchViewport.h"

class SCCWorkbench : public SDockTab
{

	SLATE_BEGIN_ARGS(SCCWorkbench)
	{}
	
	SLATE_END_ARGS()
	
private:

	TSharedPtr<class SCCWorkbenchViewport> PreviewViewport;


public:

	void Construct(const FArguments& InArgs);

};