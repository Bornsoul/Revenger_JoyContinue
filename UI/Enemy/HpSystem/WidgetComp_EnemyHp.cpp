// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetComp_EnemyHp.h"
#include "Widget_EnemyHp.h"

UWidgetComp_EnemyHp::UWidgetComp_EnemyHp()
{

	static ConstructorHelpers::FObjectFinder<UClass> Const_Hp(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_EnemyHP.BP_EnemyHP_C"));
	if (Const_Hp.Succeeded() == true)
	{
		m_pWidget_Hp_Inst = Const_Hp.Object;
	}

	SetWidgetSpace(EWidgetSpace::Screen);
}

void UWidgetComp_EnemyHp::BeginPlay()
{
	Super::BeginPlay();

	if (m_pWidget_Hp_Inst != nullptr)
	{
		SetWidgetClass(m_pWidget_Hp_Inst);
	}

	m_pEnemyHp = Cast<UWidget_EnemyHp>(GetUserWidgetObject());
	if (m_pEnemyHp == nullptr)
	{
		ULOG(TEXT("Widget Enemy Hp is nullptr"));
	}
	
	m_bAcitive = true;
	m_bDestroy = false;
	ULOG(TEXT("WidgetComp Begin"));
}

void UWidgetComp_EnemyHp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void UWidgetComp_EnemyHp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UWidgetComp_EnemyHp::Init(int32 nHpCount)
{
	//m_nHpCount = nHpCount;



	//for (int32 i = 0; i < m_nHpCount; i++)
	//{
	//	m_pEnemyHp.Add(Cast<UWidget_EnemyHp>(GetUserWidgetObject()));
	//	if (m_pEnemyHp[i] == nullptr)
	//	{
	//		ULOG(TEXT("EnemyHp is nullptr"));
	//		return;
	//	}
	//	else
	//	{
	//		//m_pEnemyHp[i]->SetPositionInViewport(FVector2D(0.0f * i * 10.0f, 0.0f));
	//	}
	//}


	//for (int32 i = 0; i < m_nHpCount; i++)
	//{
	//	m_pEnemyHp[i]->SetRenderTranslation(FVector2D(i * 10.0f, 0.0f));
	//	//m_pEnemyHp[i]->SetDesiredSizeInViewport(FVector2D(50.0f*i * 50.0f, 0.0f));
	//	//m_pEnemyHp[i]->SetPositionInViewport(FVector2D(50.0f*i * 50.0f, 0.0f));
	//	ULOG(TEXT("Postit"));		
	//}
}

void UWidgetComp_EnemyHp::SetHit()
{
	m_bAcitive = false;
	m_pEnemyHp->SetHit();
}

void UWidgetComp_EnemyHp::SetDestroy()
{
	if (m_bDestroy == true) return;
	m_bDestroy = true;
	m_pEnemyHp->SetDestroy();
}