// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_PressKeyItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_PressKeyItem : public UWidget_Root
{
	GENERATED_BODY()

private:

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
