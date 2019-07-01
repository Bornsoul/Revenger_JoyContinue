// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_WidgetDialog.h"
#include "Widget_Dialog.h"
#include "Res_DialogList.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

UCpt_WidgetDialog::UCpt_WidgetDialog()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Dialog/BP_Widget_Dialog.BP_Widget_Dialog_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}

void UCpt_WidgetDialog::BeginPlay()
{
	Super::BeginPlay();
	
	InitDialog();
}

void UCpt_WidgetDialog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (m_pWidget != nullptr) 
	{
		m_pWidget->RemoveFromParent();
		m_pWidget = nullptr;
	}
		
	m_pInst_Widget = nullptr;

	m_pDialogList.Empty();
	//m_pDialogList = nullptr;
	/*for (int i = 0; i < m_pDialogList.Num(); i++)
	{
		if (m_pDialogList[i] != nullptr)
		{
			if ( m_pDialogList[i]->)
			m_pDialogList[i]->ConditionalBeginDestroy();
			m_pDialogList[i] = nullptr;
		}
	}*/
	

	ULOG(TEXT("Dialog Destroyed"));
}

void UCpt_WidgetDialog::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*if (m_bDialoging == true)
	{
		m_fStartTime_Curr += DeltaTime;

		if (m_fStartTime_Curr >= 0.3f)
		{
			if (m_pKeyStateMng->GetKeyIsJustRelease(EKeys::SpaceBar) ||
				m_pKeyStateMng->GetKeyIsJustRelease(EKeys::LeftMouseButton))
			{
				m_fStartTime_Curr = 0.0f;
				DialogStart();
				return;
			}
		}
	}*/
}

void UCpt_WidgetDialog::InitDialog()
{
	if (m_pInst_Widget == nullptr) return;

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_Dialog* pObj = CreateWidget<UWidget_Dialog>(pPlayerController, m_pInst_Widget);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		pObj->SetShow(false);
		m_pWidget = pObj;
	}
}

//void UCpt_WidgetDialog::AddDialogList(FString sPath)
//{
//	//ULOG(TEXT("Path : %s"), *sPath);
//	ConstructorHelpers::FClassFinder<URes_DialogList> Const_DialogList(*sPath);
//	if (Const_DialogList.Succeeded())
//	{
//		URes_DialogList* pList = Const_DialogList.Class->GetDefaultObject<URes_DialogList>();
//		if (pList != nullptr) 
//		{		
//			m_pDialogList = pList;
//		}
//	}
//}

//void UCpt_WidgetDialog::AddDialogList(class TSubclassOf<class URes_DialogList> pList)
//{
//	if (pList == nullptr)
//	{
//		ULOG(TEXT("Add DialogList is nullptr"));
//		return;
//	}
//	check(pList->IsChildOf(URes_DialogList::StaticClass()));
//	
//	URes_DialogList* pSrc = NewObject<URes_DialogList>(this, pList);// pList->GetClass()->GetDefaultObject<URes_DialogList>();
//	if (pSrc != nullptr)
//	{
//		ULOG(TEXT("Dialog Tsubclass Successed"));
//		m_pDialogList = pSrc;
//	}
//}

bool UCpt_WidgetDialog::PlayDialog(int32 nGroup, int32 nStartIndex)
{
	if (m_pWidget == nullptr)
	{
		ULOG(TEXT("Widget is nullptr"));
		return false;
	}
	
	if (nGroup >= m_pDialogList.Num() )
	{
		ULOG(TEXT("Group Num is nullptr"));
		return false;
	}

	if (nStartIndex >= GetGroup_StringLenght(nGroup) )
	{
		SetDestroy();
		ULOG(TEXT("Index is nullptr"));
		return false;
	}

	if (m_bDialoging == false)
		m_pWidget->SetStartAnimation("Show");
	
	m_bDialoging = true;
	m_pWidget->SetShow(true);	
	m_pWidget->SetStartAnimation("Start");
	m_pWidget->SetCharImage(GetDialogTexture(nGroup)[nStartIndex]);
	m_pWidget->SetNameColor(GetDialogNameColor(nGroup)[nStartIndex]);
	m_pWidget->SetDialogInit(
		GetDialogString(E_DialogType::E_TYPE_NAME, nGroup)[nStartIndex],
		GetDialogString(E_DialogType::E_TYPE_SUBNAME, nGroup)[nStartIndex],
		GetDialogString(E_DialogType::E_TYPE_DIALOG, nGroup)[nStartIndex]);
	
	return true;
}

bool UCpt_WidgetDialog::DialogStart()
{
	if (GetIsTyping())
	{
		SkipDialog();
		return true;
	}

	bool bDialog = PlayDialog(m_nDialogGroup, m_nDialogIndex);
	if (bDialog == false)
	{
		m_nDialogGroup = 0;
		m_nDialogIndex = 0;
		return false;
	}
	m_nDialogIndex++;

	return true;
}

bool UCpt_WidgetDialog::SkipDialog()
{
	if (m_pWidget == nullptr) return false;
	
	return m_pWidget->SkipDialog();
}

void UCpt_WidgetDialog::SetDestroy()
{
	m_bDialoging = false;
	//m_pWidget->SetShow(false);
	m_pWidget->SetStartAnimation("Show", true);

}

TArray<FString> UCpt_WidgetDialog::GetDialogString(E_DialogType eType, int32 nGroup)
{
	TArray<FString> pString;

	for (int32 i = 0; i < m_pDialogList.Num(); i++)
	{
		if (m_pDialogList[i].m_nGroup == nGroup)
		{
			switch (eType)
			{
			case E_DialogType::E_TYPE_NAME:
				pString.Add(m_pDialogList[i].m_sName);
				break;
			case E_DialogType::E_TYPE_SUBNAME:
				pString.Add(m_pDialogList[i].m_sSubName);
				break;
			case E_DialogType::E_TYPE_DIALOG:
				pString.Add(m_pDialogList[i].m_sDialog);
				break;
			}
		}
	}
	
	return pString;
}

TArray<UTexture2D*> UCpt_WidgetDialog::GetDialogTexture(int32 nGroup)
{
	TArray<UTexture2D*> pTextrues;

	for (int32 i = 0; i < m_pDialogList.Num(); i++)
	{
		if (m_pDialogList[i].m_nGroup == nGroup)
		{
			pTextrues.Add(m_pDialogList[i].m_pCharacterImg);			
		}
	}

	return pTextrues;
}

TArray<FLinearColor> UCpt_WidgetDialog::GetDialogNameColor(int32 nGroup)
{
	TArray<FLinearColor> pColors;

	for (int32 i = 0; i < m_pDialogList.Num(); i++)
	{
		if (m_pDialogList[i].m_nGroup == nGroup)
		{
			pColors.Add(m_pDialogList[i].m_cNameColor);
		}
	}

	return pColors;
}

int32 UCpt_WidgetDialog::GetGroup_StringLenght(int32 nGroup)
{
	int32 nGroupInCount = 0;

	for (int32 i = 0; i < m_pDialogList.Num(); i++)
	{
		if (m_pDialogList[i].m_nGroup == nGroup)
		{
			nGroupInCount++;
		}
	}

	return nGroupInCount;
}

int32 UCpt_WidgetDialog::GetDialogLenght()
{
	return m_pDialogList.Num();
}

bool UCpt_WidgetDialog::GetIsTyping()
{
	if (m_pWidget == nullptr) return false;

	return m_pWidget->GetIsTyping();
}