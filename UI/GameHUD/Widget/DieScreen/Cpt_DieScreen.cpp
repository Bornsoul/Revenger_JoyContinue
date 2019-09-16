#include "Cpt_DieScreen.h"
#include "Widget_Die.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

UCpt_DieScreen::UCpt_DieScreen()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_ResultHUD(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/Die/BP_Widget_Die.BP_Widget_Die_C")); 

	if (Const_ResultHUD.Succeeded())
	{
		m_pInst_Widget = Const_ResultHUD.Object;
	}

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));

}

void UCpt_DieScreen::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pWidget = CreateWidget<UWidget_Die>(pPlayerController, m_pInst_Widget);
	if (m_pWidget != nullptr)
	{
		m_pWidget->AddToViewport();
		m_pWidget->SetActive(false);
	}
	m_bActive = false;
}

void UCpt_DieScreen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pInst_Widget != nullptr)
	{
		if (m_pInst_Widget->IsValidLowLevel())
		{
			m_pInst_Widget = nullptr;
		}
	}

	if (m_pWidget != nullptr)
	{
		if (m_pWidget->IsValidLowLevel())
		{
			m_pWidget = nullptr;
		}
	}

	if (m_pKeyStateMng != nullptr)
	{
		if (m_pKeyStateMng->IsValidLowLevel())
		{
			m_pKeyStateMng = nullptr;
		}
	}
}

void UCpt_DieScreen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (m_bActive == false) return; 
	if (m_pWidget == nullptr) return;

	if (m_bDieStart)
	{			
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fDieStartTime_Cur >= m_fDieStartTime_End)
		{
			m_pWidget->SetActive(true);
			m_pWidget->SetPlayAnimation("Start");
			m_pWidget->Active_DieTime(10.0f);
			m_bKeyTime = true;

			m_bDieStart = false;
		}			
	}
	if (m_bKeyTime)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fKeyTime_Cur >= m_fKeyTime_End)
		{
			if (m_pKeyStateMng->GetKeyIsDown(EKeys::LeftMouseButton))
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("Loading"), true);
				m_bActive = false;
				m_bKeyTime = false;
				return;
			}
		}
	}
}

void UCpt_DieScreen::Active_Die(float fDieStartTime)
{
	if (m_pWidget == nullptr) return;	

	m_fDieStartTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	m_fDieStartTime_End = fDieStartTime;
	m_bDieStart = true;
	m_fKeyTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	m_bActive = true;
}

void UCpt_DieScreen::DeActive_Die()
{
	if (m_pWidget == nullptr) return;	
	m_bActive = false;
}

int32 UCpt_DieScreen::Menu_GetButton()
{
	if (m_pWidget == nullptr) return 0;

	return m_pWidget->GetCurrentState();
}

bool UCpt_DieScreen::GetAniPlaying()
{
	if (m_pWidget == nullptr) return false;

	return m_pWidget->GetAniPlaying();
}