// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/WidgetComponent.h"
#include "WidgetComp_EnemyHp.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidgetComp_EnemyHp : public UWidgetComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TSubclassOf<class UWidget_EnemyHp> m_pWidget_Hp_Inst;

	UPROPERTY()
		class UWidget_EnemyHp* m_pEnemyHp;

	bool m_bAcitive = false;
	bool m_bDestroy = false;

public:
	UWidgetComp_EnemyHp();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(int32 nHpCount);
	void SetHit();
	void SetDestroy();

	FORCEINLINE bool GetActive() { return m_bAcitive; }
};
