// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget_QuestAlarmHUD.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_QuestAlarm.generated.h"

enum class eQuestIcon : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_QuestAlarm : public UActorComponent
{
	GENERATED_BODY()
//
//private:
//	UPROPERTY()
//		class AHUD_Game* m_pHud;
//
//	UPROPERTY()
//		TSubclassOf<class UWidget_QuestAlarm_Item> m_pInst_AlarmItem;
//
//	FTimerHandle m_pTimer;
//
//public:		
//	UCpt_QuestAlarm();
//	virtual void BeginPlay() override;
//	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	void SetHudInit();
//
//	UFUNCTION(BlueprintCallable)
//		void SetWorldName(eQuestIcon eIcon, FText sText);
//
//	UFUNCTION(BlueprintCallable)
//		void Add_Quest(eQuestIcon eIcon, FText sText);
//		
//	UFUNCTION(BlueprintCallable)
//		void Done_Quest(int nIndex = 0, float fDestroyDelay = 1.0f);
//
//	UFUNCTION(BlueprintCallable)
//		void Destroy_Quest(int nIndex = 0);
//
//	UFUNCTION(BlueprintCallable)
//		bool DestroyAll_Quest();
//
//	UFUNCTION(BlueprintPure)
//		int32 GetQuestItemNum();
};
