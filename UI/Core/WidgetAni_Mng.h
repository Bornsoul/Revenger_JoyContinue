// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Widget.h"
#include "Styling/SlateColor.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "WidgetAni_Mng.generated.h"

UCLASS()
class REVENGER_API UWidgetAni_Mng : public UObject
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UUserWidget* m_pWidget;
	
	UPROPERTY()
		TMap<FString, class UWidgetAnimation*> m_pAnimations;

public:
	UWidgetAni_Mng();

	void Init(class UUserWidget* pWidget);
	void Destroy();

	//! 해당 애니메이션 플레이
	//! sAniName = 애니메이션 이름	
	void SetPlayAnimation(FString sAniName, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float fStartTime = 0.0f, int32 nLoop = 1, float fAniSpeed = 1.0f);


	//! 애니메이션 리스트 담음
	void SetAnimation(TMap<FString, class UWidgetAnimation*>& pResult);


};
