// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_KeyInputMng.h"
#include "Widget_KeyInputHUD.h"

UCpt_KeyInputMng::UCpt_KeyInputMng()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Tutorial_Widget/BP_Widget_KeyInputHUD.BP_Widget_KeyInputHUD_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_InputHud = Const_Widget.Object;
	}

}

void UCpt_KeyInputMng::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pKeyInputHud = CreateWidget<UWidget_KeyInputHUD>(pController, m_pInst_InputHud);
	if (m_pKeyInputHud != nullptr)
	{
		m_pKeyInputHud->AddToViewport();
		m_pKeyInputHud->SetActive(false);
	}

	m_stKeyList.Empty();
	m_bCreatedKey = false;
	m_bEndComponent = true;
	m_fRemoveHud = 0.0f;
}

void UCpt_KeyInputMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pKeyInputHud != nullptr)
	{
		if (m_pKeyInputHud->IsValidLowLevel())
		{
			m_pKeyInputHud->RemoveFromParent();
			m_pKeyInputHud = nullptr;			
		}
	}

	m_stCreateKeyList.Empty();
	m_stKeyList.Empty();
}

void UCpt_KeyInputMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (m_bCreatedKey == true)
	{
		if (m_stKeyList.Num() > 0)
		{
			if (pController != nullptr)
			{
				for (int i = 0; i < m_stKeyList.Num(); i++)
				{
					if (pController->WasInputKeyJustPressed(m_stKeyList[i]) == true)
					{
						Press_Inputkey(m_stKeyList[i].GetDisplayName());
						m_stKeyList.RemoveAt(i);
						return;
					}
				}
			}
		}
		else
		{
			if (m_bEndComponent == false) return;

			m_fRemoveHud += DeltaTime;
			if (m_fRemoveHud >= m_fRemoveHud_Time)
			{
				if (m_pKeyInputHud != nullptr)
				{
					m_pKeyInputHud->SetPlayAnimation("End");
				}

				m_bCreatedKey = false;
				m_fRemoveHud = 0.0f;
				return;
			}			
		}
	}
	else
	{
		if (m_bEndComponent == false) return;

		if (m_bSuccess == false)
		{
			if (m_pKeyInputHud != nullptr)
			{
				if (m_pKeyInputHud->GetKeyInputSuccess())
				{
					m_bSuccess = true;
					return;
				}
			}
		}
	}

}

void UCpt_KeyInputMng::Create_InputKeySubTitle(const FText sTitle, const FText sSubTitle, const TArray<FKey> stKeyList, const float fRemoveTime, const bool bEndComp)
{	
	
	if (fRemoveTime > 0.0f)
	{
		m_fRemoveHud_Time = fRemoveTime;
	}

	m_bEndComponent = bEndComp;

	if (m_pKeyInputHud != nullptr)
	{
		SetTitleAndSubTitle(sTitle, sSubTitle);

		m_pKeyInputHud->SetActive(true);
		m_pKeyInputHud->SetPlayAnimation("Start");
	}

	if (stKeyList.Num() > 0)
	{
		m_stCreateKeyList.Empty();
		for (int i = 0; i < stKeyList.Num(); i++)
		{
			Create_InputKey(stKeyList[i]);
			m_stCreateKeyList.Add(stKeyList[i]);
		}
	}	
}

void UCpt_KeyInputMng::SetTitleAndSubTitle(const FText sTitle, const FText sSubTitle)
{
	if (m_pKeyInputHud != nullptr)
	{
		m_pKeyInputHud->SetTitleAndSubTitle(sTitle, sSubTitle);
	}
}

bool UCpt_KeyInputMng::Create_InputKey(const FKey stKey)
{
	if (m_pKeyInputHud == nullptr)
	{
		return false;
	}

	m_pKeyInputHud->Create_KeyItem(stKey.GetDisplayName());
	m_stKeyList.Add(stKey);
	m_bCreatedKey = true;
	m_bSuccess = false;
	return true;
}

bool UCpt_KeyInputMng::Press_Inputkey(const FText sKeyName)
{
	if (m_stKeyList.Num() > 0)
	{
		if (m_pKeyInputHud != nullptr)
		{
			//ULOG(TEXT("Press Key : %s"), *sKeyName.ToString());
			m_pKeyInputHud->Success_KeyInput(sKeyName);			
			return true;
		}
	}

	return false;
}

bool UCpt_KeyInputMng::Press_Inputkeys(const TArray<FKey> sKeyNameList)
{
	m_stKeyList.Empty();

	if (sKeyNameList.Num() > 0)
	{
		if (m_pKeyInputHud != nullptr)
		{
			for (int i = 0; i < sKeyNameList.Num(); i++)
			{
				m_pKeyInputHud->Success_KeyInput(sKeyNameList[i].GetDisplayName());
			}	
			return true;
		}
	}

	return false;
}

bool UCpt_KeyInputMng::Refresh_InputKeys()
{
	m_stKeyList = m_stCreateKeyList;

	if (m_stCreateKeyList.Num() > 0)
	{
		if (m_pKeyInputHud != nullptr)
		{
			for (int i = 0; i < m_stCreateKeyList.Num(); i++)
			{
				m_pKeyInputHud->Fail_KeyInput(m_stCreateKeyList[i].GetDisplayName());

			}			
			return true;
		}
	}

	return false;
}

bool UCpt_KeyInputMng::Refresh_InputKey(const FKey stKey)
{
	m_stKeyList = m_stCreateKeyList;

	if (m_stCreateKeyList.Num() > 0)
	{
		if (m_pKeyInputHud != nullptr)
		{
			m_pKeyInputHud->Fail_KeyInput(stKey.GetDisplayName());
			return true;
		}
	}

	return false;
}

bool UCpt_KeyInputMng::GetSuccess()
{
	return m_bSuccess;
}