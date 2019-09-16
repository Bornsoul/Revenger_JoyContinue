// Fill out your copyright notice in the Description page of Project Settings.

#include "Obj_AlertPopup.h"
#include "Widget_AlertPopup.h"

UObj_AlertPopup::UObj_AlertPopup()
{
	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Popup/BP_Widget_Alert.BP_Widget_Alert_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Alert = Const_Widget.Object;
	}	
}

class UWidget_AlertPopup* UObj_AlertPopup::CreateAlert(const FString sText, const float fDestroyTime)
{
	APlayerController* pController = UGameplayStatics::GetPlayerController(UObject::GetWorld(), 0);
	if (pController != nullptr)
	{
		UWidget_AlertPopup* pObj = CreateWidget<UWidget_AlertPopup>(pController, m_pInst_Alert);
		if (pObj != nullptr)
		{			
			pObj->AddToViewport(50);			
			pObj->SetTimer(fDestroyTime);
			pObj->SetText(FText::FromString(sText));
			pObj->SetPlayAnimation("Start");

			return pObj;
		}
	}

	return nullptr;
}