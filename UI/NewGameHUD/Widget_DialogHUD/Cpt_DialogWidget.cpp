#include "Cpt_DialogWidget.h"
#include "Widget_DialogHUD.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

UCpt_DialogWidget::UCpt_DialogWidget()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Dialog_Widget/BP_Widget_Dialog.BP_Widget_Dialog_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_HudWidget= Const_Widget.Object;
	}

}

void UCpt_DialogWidget::BeginPlay()
{
	Super::BeginPlay();


	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pDialogHUD = CreateWidget<UWidget_DialogHUD>(pPlayerController, m_pInst_HudWidget);
	if (m_pDialogHUD != nullptr)
	{
		m_pDialogHUD->AddToViewport();
		m_pDialogHUD->SetActive(false);
	}

	m_nDialogIndex = 0;

}

void UCpt_DialogWidget::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (m_pDialogHUD != nullptr)
	{
		if (m_pDialogHUD->IsValidLowLevel())
		{
			m_pDialogHUD = nullptr;
		}
	}

	if (m_pKeyStateMng != nullptr)
	{
		if (m_pKeyStateMng->IsValidLowLevel())
		{
			m_pKeyStateMng = nullptr;
		}
	}

	if (m_pInst_HudWidget != nullptr)
	{
		if (m_pInst_HudWidget->IsValidLowLevel())
		{
			m_pInst_HudWidget = nullptr;
		}
	}

	m_pDialogList.Empty();
}

void UCpt_DialogWidget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bDestory)
	{
		if (m_pDialogHUD->GetActive() == false)
		{
			m_bActiveDialog = false;
			m_bDestory = false;
			return;
		}
	}
}

bool UCpt_DialogWidget::Active_Dialog()
{
	if (m_pDialogHUD == nullptr || m_pDialogList.Num() <= 0)
	{
		ULOG(TEXT("Active Dialog is nullptr"));
		DeActive_Dialog();
		return false;
	}
	m_nDialogIndex = 0;
	m_bDestory = false;
	m_pDialogHUD->SetActive(true);
	m_pDialogHUD->SetDialogTextSpeed(m_fDialogTextSpeed);
	SetDialogData(m_nDialogIndex);

	m_bActiveDialog = true;

	//ULOG(TEXT("Active Dialog")); 
	return true;
}

bool UCpt_DialogWidget::Active_NextDialog()
{
	if (m_bActiveDialog == false)
	{
		ULOG(TEXT("Not Active Dialog"));
		return false;
	}

	if (m_pDialogHUD->GetIsPlaying())
	{
		m_pDialogHUD->Skip_Dialog();
		return true;
	}

	m_nDialogIndex++;

	if (m_nDialogIndex >= m_pDialogList.Num())
	{
		m_nDialogIndex = m_pDialogList.Num();
		DeActive_Dialog();
		return false;
	}
	SetDialogData(m_nDialogIndex);
	return true;
}

void UCpt_DialogWidget::DeActive_Dialog()
{
	m_nDialogIndex = 0;	
	m_pDialogHUD->SetPlayAnimation("End");	
	m_bDestory = true;
}

bool UCpt_DialogWidget::Skip_Dialog()
{
	if (m_pDialogHUD == nullptr) return false;
	if (m_pDialogList.Num() <= 0) return false;

	m_pDialogHUD->Skip_Dialog();
	//SetDialogData(m_nDialogIndex);
	return true;
}

void UCpt_DialogWidget::SetDialogData(int32 nIndex)
{
	if (m_pDialogHUD == nullptr)return;
	if (m_pDialogList.Num() <= 0) return;

	if (m_pDialogList[nIndex].m_bUseMediaTexture == true)
	{
		m_pDialogHUD->SetMediaData(m_pDialogList[nIndex].m_pMediaMat, m_pDialogList[nIndex].m_pMediaSource);
	}

	m_pDialogHUD->SetDialogCount(nIndex, m_pDialogList.Num());

	m_pDialogHUD->SetDialogData(
		m_pDialogList[nIndex].m_bImageList_Random,
		m_pDialogList[nIndex].m_pImgList,
		m_pDialogList[nIndex].m_sName,
		m_pDialogList[nIndex].m_sSubName,
		m_pDialogList[nIndex].m_sText);

	//ULOG(TEXT("DialogData Send"));
}