// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "Templates/SharedPointer.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"

class SCCWorkbenchViewport : public SEditorViewport
{
public:

	SLATE_BEGIN_ARGS(SCCWorkbenchViewport)
	{}
	SLATE_END_ARGS()

private:

	TSharedPtr<FEditorViewportClient> ViewportClient;

};