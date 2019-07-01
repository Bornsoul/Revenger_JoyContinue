#include "Cpt_EnemyBossHp.h"
#include "Widget_EnemyBossHp.h"
#include "Widget_EnemyBossTitle.h"


UCpt_EnemyBossHp::UCpt_EnemyBossHp()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_TitleWidget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_EnemyBossTitle.BP_EnemyBossTitle_C"));
	if (Const_TitleWidget.Succeeded())
	{
		m_pInst_TitleWidget = Const_TitleWidget.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_HpWidget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_BossHp.BP_BossHp_C"));
	if (Const_HpWidget.Succeeded())
	{
		m_pInst_HpWidget = Const_HpWidget.Object;
	}

}

void UCpt_EnemyBossHp::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCpt_EnemyBossHp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (int i = 0; i < m_pHpWidgetList.Num(); i++)
	{
		if (m_pHpWidgetList[i] != nullptr)
		{
			m_pHpWidgetList[i]->RemoveFromParent();
			m_pHpWidgetList[i] = nullptr;
		}
	}
	m_pHpWidgetList.Empty();

	if (m_pTitleWidget != nullptr)
	{
		m_pTitleWidget->RemoveFromParent();
		m_pTitleWidget = nullptr;
	}
}

void UCpt_EnemyBossHp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UCpt_EnemyBossHp::SetHpStart()
{
	if (m_pTitleWidget == nullptr) return;

	m_pTitleWidget->SetActive(true);
	for (int i = 0; i < m_pHpWidgetList.Num(); i++)
	{
		if (m_pHpWidgetList[i] != nullptr)
		{
			m_pHpWidgetList[i]->SetActive(true);
		}
	}
}

void UCpt_EnemyBossHp::AddHeart(int32 nHp)
{
	if (m_pInst_TitleWidget == nullptr) return;
	if (m_pInst_HpWidget == nullptr) return;

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_EnemyBossTitle* pObj = CreateWidget<UWidget_EnemyBossTitle>(pPlayerController, m_pInst_TitleWidget);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		pObj->SetActive(true);
		m_pTitleWidget = pObj;
	}

	for (int i = 0; i < nHp; i++)
	{
		APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UWidget_EnemyBossHp* pObj = CreateWidget<UWidget_EnemyBossHp>(pPlayerController, m_pInst_HpWidget);
		if (pObj != nullptr)
		{
			pObj->AddToViewport();
			pObj->SetActive(true);
			m_pHpWidgetList.Add(pObj);
		}
	}

}

void UCpt_EnemyBossHp::SetHeartPosition(FVector2D vPos, float fSize)
{
	for (int i = 0; i < m_pHpWidgetList.Num(); i++)
	{
		if (m_pHpWidgetList[i] != nullptr)
		{
			m_pHpWidgetList[i]->SetPositionInViewport(FVector2D(vPos.X + i * fSize, vPos.Y));
		}
	}
}

void UCpt_EnemyBossHp::SetHit()
{
	if (m_pHpWidgetList[0]->GetIsHit() == true)
	{
		ULOG(TEXT("All Hit"));
		return;
	}

	m_pTitleWidget->SetHit();
	for (int i = m_pHpWidgetList.Num()-1; i >= 0; i--)
	{
		if (m_pHpWidgetList[i] != nullptr)
		{
			if (m_pHpWidgetList[i]->GetIsHit() == false)
			{
				
				m_pHpWidgetList[i]->SetHit();				
				return;
			}
		}
	}
}

void UCpt_EnemyBossHp::SetDestroy()
{
	m_pTitleWidget->SetActive(false);
	for (int i = 0; i < m_pHpWidgetList.Num(); i++)
	{
		if (m_pHpWidgetList[i] != nullptr)
		{
			m_pHpWidgetList[i]->SetActive(false);
		}
	}
}