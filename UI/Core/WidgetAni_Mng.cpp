// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetAni_Mng.h"
#include "RunTime/UMG/Public/Blueprint/UserWidget.h"

UWidgetAni_Mng::UWidgetAni_Mng()
{
}

void UWidgetAni_Mng::Init(class UUserWidget* pWidget)
{
	m_pWidget = pWidget;

	if (m_pWidget == nullptr)
	{
		ULOG(TEXT("WidgetAni Root is nullptr"));
		return;
	}

	m_pAnimations.Empty();
	SetAnimation(m_pAnimations);

	/*for (TMap<FString, class UWidgetAnimation*>::TIterator it = m_pAnimations.CreateIterator(); it; ++it)
	{
		ULOG(TEXT("AniList : %s"), *it->Key);
	}*/
}

void UWidgetAni_Mng::SetAnimation(TMap<FString, class UWidgetAnimation*>& pResult)
{
	pResult.Empty();

	UProperty* pProperty = m_pWidget->GetClass()->PropertyLink;
	if (pProperty != nullptr)
	{
		while (pProperty != nullptr)
		{
			if (pProperty->GetClass() == UObjectProperty::StaticClass())
			{
				UObjectProperty* pObjectProperty = Cast<UObjectProperty>(pProperty);

				if (pObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					UObject* pObject = pObjectProperty->GetObjectPropertyValue_InContainer(m_pWidget);
					UWidgetAnimation* pWidgetAni = Cast<UWidgetAnimation>(pObject);

					if (pWidgetAni != nullptr)
					{
						//ULOG(TEXT("Ani Add"));
						FString sName = pWidgetAni->GetMovieScene()->GetFName().ToString();
						pResult.Add(sName, pWidgetAni);
					}
				}
			}
			pProperty = pProperty->PropertyLinkNext;
		}
	}
	else
	{
		ULOG(TEXT("Property is nullptr"));
		return;
	}
}

void UWidgetAni_Mng::SetPlayAnimation(FString sAniName, EUMGSequencePlayMode::Type PlayMode, float fStartTime, int32 nLoop, float fAniSpeed)
{
	for (TMap<FString, class UWidgetAnimation*>::TIterator it = m_pAnimations.CreateIterator(); it; ++it)
	{
		if (it->Key == sAniName)
		{			
			if (m_pWidget != nullptr) 
			{
				m_pWidget->PlayAnimation(it->Value, fStartTime, nLoop, PlayMode, fAniSpeed);
				//ULOG(TEXT("PlayAnimation : %s"), *sAniName);
				return;
			}						
		}		
	}
}
