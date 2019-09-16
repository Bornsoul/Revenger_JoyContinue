// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_QuestAlarm.h"
//#include "UI/NewGameHUD/HUD_Game.h"
//#include "UI/NewGameHUD/Widget/Widget_QuestAlarm/Widget_QuestAlarm_Item.h"
//#include "TimerManager.h"
//
//UCpt_QuestAlarm::UCpt_QuestAlarm()
//{
//	PrimaryComponentTick.bCanEverTick = false;
//
//	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/QuestAlarm_Widget/BP_Widget_QuestAlarmItem.BP_Widget_QuestAlarmItem_C"));
//
//	if (Const_Widget.Succeeded())
//	{
//		m_pInst_AlarmItem = Const_Widget.Object; 
//	}
//}
//
//void UCpt_QuestAlarm::BeginPlay()
//{
//	Super::BeginPlay();
//	
//	m_pHud = Cast<AHUD_Game>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
//	if (m_pHud == nullptr)
//	{
//		ULOG(TEXT("Hud is nullptr"));
//		return;
//	}
//
//	//m_pHud->GetRootHUD()->GetQuestHUD()->SetAlarmItemRoot(m_pInst_AlarmItem);
//
//	//GetOwner()->GetWorldTimerManager().SetTimer(m_pTimer, this, &UCpt_QuestAlarm::SetHudInit, 0.5f, false);
// 
//}
//
//void UCpt_QuestAlarm::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	Super::EndPlay(EndPlayReason);
//
//	if (m_pHud)
//	{
//		if (m_pHud->IsValidLowLevel())
//		{
//			m_pHud = nullptr;
//		}
//	}
//	
//	GetOwner()->GetWorldTimerManager().ClearTimer(m_pTimer);
//	//m_pTimer = nullptr;	
//}
//
//void UCpt_QuestAlarm::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}
//
//void UCpt_QuestAlarm::SetHudInit()
//{
//	m_pHud = Cast<AHUD_Game>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
//	if (m_pHud == nullptr)
//	{
//		ULOG(TEXT("Hud is nullptr"));
//		return;
//	}
//
//	ULOG(TEXT("Quest Component is Ready"));
//	GetOwner()->GetWorldTimerManager().ClearTimer(m_pTimer);
//}
//
//void UCpt_QuestAlarm::SetWorldName(eQuestIcon eIcon, FText sText)
//{
//	if (m_pHud == nullptr) return;
//
//	m_pHud->GetRootHUD()->GetQuestHUD()->SetWorldName(eIcon, sText);
//}
//
//void UCpt_QuestAlarm::Add_Quest(eQuestIcon eIcon, FText sText)
//{
//	if (m_pHud == nullptr) return;
//
//	m_pHud->GetRootHUD()->GetQuestHUD()->Add_Quest(eIcon, sText);	
//}
//
//void UCpt_QuestAlarm::Done_Quest(int nIndex, float fDestroyDelay)
//{
//	if (m_pHud == nullptr) return;
//
//	m_pHud->GetRootHUD()->GetQuestHUD()->Done_Quest(nIndex, fDestroyDelay);
//}
//
//
//void UCpt_QuestAlarm::Destroy_Quest(int nIndex)
//{
//	if (m_pHud == nullptr) return;
//
//	m_pHud->GetRootHUD()->GetQuestHUD()->Destroy_Quest(nIndex);
//}
//
//bool UCpt_QuestAlarm::DestroyAll_Quest()
//{
//	if (m_pHud == nullptr) return false;
//	
//	return m_pHud->GetRootHUD()->GetQuestHUD()->DestroyAll_Quest();
//}
//
//int32 UCpt_QuestAlarm::GetQuestItemNum()
//{
//	if (m_pHud == nullptr)
//	{
//		return -1;
//	}
//
//	return m_pHud->GetRootHUD()->GetQuestHUD()->GetQuestItemNum()-1;
//}
