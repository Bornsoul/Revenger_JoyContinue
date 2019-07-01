// Fill out your copyright notice in the Description page of Project Settings.

#include "SC_WidgetEnemyHp.h"
#include "UI/Enemy/HpSystem/WidgetComp_EnemyHp.h"

#include "Components/BoxComponent.h"

USC_WidgetEnemyHp::USC_WidgetEnemyHp()
{
	PrimaryComponentTick.bCanEverTick = false;

	m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));	
	m_pBox->SetupAttachment(this);
	//m_pBox->bHiddenInGame = true;

	for (int i = 0; i < 3; i++)
	{
		FString sStr = FString::Printf(TEXT("HpComp_%d"), i);
		m_pEnemyHp.Add(CreateDefaultSubobject<UWidgetComp_EnemyHp>(FName(*sStr)));

		if (m_pEnemyHp[i] != nullptr)
		{
			m_pEnemyHp[i]->SetupAttachment(m_pBox);
		}
	}
	//ULOG(TEXT("SC : %d"), nCnt);

}

void USC_WidgetEnemyHp::SetInit(int nCnt)
{

	//m_pEnemyHp.Empty();

	//FString sPath = "/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_WidgetComp_EnemyHp.BP_WidgetComp_EnemyHp_C";
	//FText TextVariable = FText::AsCultureInvariant(sPath);
	//ConstructorHelpers::FClassFinder<UWidgetComp_EnemyHp> Const_List(*sPath);

	//if (Const_List.Succeeded())
	//{
	//	UWidgetComp_EnemyHp* pWidget = Const_List.Class->GetDefaultObject<UWidgetComp_EnemyHp>();
	//	pWidget->SetupAttachment(this);
	//	ULOG(TEXT("Attached"));

	//	//for (int i = 0; i < 3; i++)
	//	//{
	//	//	m_pEnemyHp.Add(Const_List.Class->GetDefaultObject<UWidgetComp_EnemyHp>());
	//	//	//m_pEnemyHp.Add(CreateDefaultSubobject<UWidgetComp_EnemyHp>(FName(*sStr)));

	//	//	if (m_pEnemyHp[i] != nullptr)
	//	//	{
	//	//		ULOG(TEXT("Attached"));
	//	//		m_pEnemyHp[i]->SetupAttachment(m_pBox);
	//	//	}
	//	//}
	//}
	//nCnt = nCnt;

	//ULOG(TEXT("Hp : %d"), nCnt);
}

void USC_WidgetEnemyHp::BeginPlay()
{
	Super::BeginPlay();

	m_bActive = true;
}

void USC_WidgetEnemyHp::Tick_Transform(FVector vLocation, float fDeltaTime)
{
	if (m_bActive == false)return;

	for (int i = 0; i < m_pEnemyHp.Num(); i++)
	{
		if (m_pEnemyHp[i] != nullptr)
		{
			m_pEnemyHp[i]->SetWorldLocation(FVector(
				vLocation.X - i * m_vHpPos.X,
				vLocation.Y + i * m_vHpPos.X,
				m_vHpPos.Y));
		}
	}
}

void USC_WidgetEnemyHp::SetHit()
{
	for (int i = m_pEnemyHp.Num() - 1; i >= 0; i--)
	{
		if (m_pEnemyHp[i] != nullptr)
		{
			if (m_pEnemyHp[i]->GetActive() == true)
			{
				m_pEnemyHp[i]->SetHit();
				break;
			}
		}
	}
}

void USC_WidgetEnemyHp::SetDestroy()
{
	for (int i = 0; i < m_pEnemyHp.Num(); i++)
	{
		if (m_pEnemyHp[i] != nullptr)
		{
			m_pEnemyHp[i]->SetDestroy();
		}
	}
}