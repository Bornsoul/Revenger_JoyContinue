#include "Cpt_ResultWidget.h"
#include "Widget_ResultHUD.h"

UCpt_ResultWidget::UCpt_ResultWidget()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_ResultHUD(TEXT("/Game/1_Project_Main/1_Blueprints/UI/ResultHUD/BP_Widget_ResultHUD.BP_Widget_ResultHUD_C"));
	if (Const_ResultHUD.Succeeded())
	{
		m_pInst_Widget = Const_ResultHUD.Object;
	}

}

void UCpt_ResultWidget::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_pInst_Widget == nullptr)
	{
		ULOG(TEXT("Instance Widget is nullptr"));
		return;
	}

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pWidget = CreateWidget<UWidget_ResultHUD>(pPlayerController, m_pInst_Widget);
	if (m_pWidget != nullptr)
	{
		m_pWidget->AddToViewport();		
	}

	m_bActive = false;
}

void UCpt_ResultWidget::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pWidget != nullptr)
	{
		if (m_pWidget->IsValidLowLevel())
		{
			m_pWidget->RemoveFromParent();		
			m_pWidget = nullptr;
		}
	}

}

void UCpt_ResultWidget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bActive == false)return;
	if (m_bEndTime == true)
	{
		if (m_pWidget->GetResultDone() == true)
		{
			m_fEndTime_Cur += DeltaTime;
			if (m_fEndTime_Cur >= m_fEndTime_End)
			{
				m_fEndTime_Cur = 0.0f;
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage_4"), true);
				m_bEndTime = false;
				return;
			}
		}
	}
}

void UCpt_ResultWidget::Active_HUD()
{
	if (m_pWidget == nullptr) return;
	
	m_pWidget->SetActive(true);
	m_pWidget->Active_HUD();
	m_bActive = true;
	m_bEndTime = true;
}

void UCpt_ResultWidget::DeActive_HUD()
{
	if (m_pWidget == nullptr) return;
	m_pWidget->DeActive_HUD();
	m_bActive = false;
}

void UCpt_ResultWidget::SetDataInit(TArray<FString> pItemTextList)
{
	if (m_pWidget == nullptr) return;

	m_pWidget->SetItemResult_Text(pItemTextList);

}