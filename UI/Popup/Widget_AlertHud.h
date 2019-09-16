// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_AlertHud.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_AlertHud : public UWidget_Root
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UScrollBox* m_pScrollBox;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void AddAlert(class UWidget_AlertPopup* pAlert);
};
