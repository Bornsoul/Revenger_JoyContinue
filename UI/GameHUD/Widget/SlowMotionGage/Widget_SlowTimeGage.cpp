// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SlowTimeGage.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Styling/SlateBrush.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SlowTimeGage::NativeConstruct()
{
	Super::NativeConstruct();

	m_pGage = Cast<UImage>(GetWidgetFromName(TEXT("Gage")));
	if (m_pGage == nullptr)
	{
		ULOG(TEXT("Error UProgressBar"));
	}

	m_pGageValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GageValue")));
	if (m_pGageValueText == nullptr)
	{
		ULOG(TEXT("Error UTextBlock"));
	}

	m_pWidgetAni = NewObject<UWidgetAni_Mng>();
	if (m_pWidgetAni != nullptr)
	{
		m_pWidgetAni->Init(this);
	}

	m_pMaterialInstance = Cast<UMaterialInterface>(m_pGage->Brush.GetResourceObject());
	if (m_pMaterialInstance == nullptr)
	{
		ULOG(TEXT("Error m_pMaterialInstance"));
	}
	else
	{
		m_pMaterialDynamic = UMaterialInstanceDynamic::Create(m_pMaterialInstance, nullptr);

		if (m_pMaterialDynamic == nullptr)
		{
			ULOG(TEXT("Error UMaterialInstanceDynamic"));
		}
		else
		{
			m_pGage->Brush.SetResourceObject(m_pMaterialDynamic);
		}
	}

}

void UWidget_SlowTimeGage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_pRootChar != nullptr)
	{
		Tick_Position();
	}

	if (m_pMaterialDynamic == nullptr) return;
	if (m_fGageValue >= 0.0f && m_fGageValue < 0.25f)
	{
		vColor.X = FMath::Lerp(vColor.X, 0.067975f, m_fGageSpeed * InDeltaTime);
		vColor.Y = FMath::Lerp(vColor.Y, 0.713542f, m_fGageSpeed * InDeltaTime);
		vColor.Z = FMath::Lerp(vColor.Z, 0.008568f, m_fGageSpeed * InDeltaTime);

	}
	if (m_fGageValue >= 0.25f && m_fGageValue < 0.5f)
	{		
		vColor.X = FMath::Lerp(vColor.X, 0.65625f, m_fGageSpeed * InDeltaTime);
		vColor.Y = FMath::Lerp(vColor.Y, 0.169107f, m_fGageSpeed * InDeltaTime);
		vColor.Z = FMath::Lerp(vColor.Z, 0.0f, m_fGageSpeed * InDeltaTime);

	}
	else if (m_fGageValue >= 0.5f && m_fGageValue < 0.75f)
	{
		vColor.X = FMath::Lerp(vColor.X, 0.708333f, m_fGageSpeed * InDeltaTime);
		vColor.Y = FMath::Lerp(vColor.Y, 0.0f, m_fGageSpeed * InDeltaTime);
		vColor.Z = FMath::Lerp(vColor.Z, 0.006973f, m_fGageSpeed * InDeltaTime);

	}
	else if (m_fGageValue >= 0.75f && m_fGageValue <= 1.0f)
	{
		vColor.X = FMath::Lerp(vColor.X, 0.0f, m_fGageSpeed * InDeltaTime);
		vColor.Y = FMath::Lerp(vColor.Y, 0.0f, m_fGageSpeed * InDeltaTime);
		vColor.Z = FMath::Lerp(vColor.Z, 0.0f, m_fGageSpeed * InDeltaTime);
	}


}

void UWidget_SlowTimeGage::SetInit(class AActor* pActor, FVector2D vPos)
{
	m_pRootChar = pActor;
	vWidgetPos = vPos;
	m_bActive = true;
	m_fGageValue = 0.0f;
	m_fGageSpeed = 2.0f;
}

void UWidget_SlowTimeGage::SetShow(bool bShow)
{
	m_bShow = bShow;
	if (bShow)
	{		
		m_pWidgetAni->SetPlayAnimation("Show");
	}
	else
	{
		m_pWidgetAni->SetPlayAnimation("Show", EUMGSequencePlayMode::Reverse);
	}
}

void UWidget_SlowTimeGage::SetActive(bool bActive)
{
	m_bActive = bActive;
	if (bActive)
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
	else
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_SlowTimeGage::Tick_Target(AActor * pActor)
{
	m_pRootChar = pActor;
}

void UWidget_SlowTimeGage::Tick_Position()
{
	FVector vPos = m_pRootChar->GetActorLocation();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector2D vScreenPos;
	pPlayerController->ProjectWorldLocationToScreen(vPos, vScreenPos);

	int32 nScreen_Width = 0;
	int32 nScreen_Height = 0;

	pPlayerController->GetViewportSize(nScreen_Width, nScreen_Height);

	int32 nScreenX = (int32)vScreenPos.X + vWidgetPos.X;
	int32 nScreenY = (int32)vScreenPos.Y + vWidgetPos.Y;

	SetPositionInViewport(FVector2D(nScreenX, nScreenY));
}

void UWidget_SlowTimeGage::SetValue(float fVal)
{
	if (m_pMaterialDynamic == nullptr) return;
	m_fGageValue = fVal;

	int32 nMax = 99;
	float fResult = fVal / 1.0f * 100.0f;
	FString sStr = FString::Printf(TEXT("%d%%"), FMath::FloorToInt(nMax - fResult)); 
	m_pGageValueText->SetText(FText::FromString(sStr));

	m_pMaterialDynamic->SetScalarParameterValue(FName(TEXT("fGageValue")), fVal);
	m_pMaterialDynamic->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor::FLinearColor(vColor.X, vColor.Y, vColor.Z));

}
