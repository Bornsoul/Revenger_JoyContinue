// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_EnemyBossHp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_EnemyBossHp : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		class TSubclassOf<class UWidget_EnemyBossHp> m_pInst_HpWidget;

	UPROPERTY()
		TArray<class UWidget_EnemyBossHp*> m_pHpWidgetList;

	UPROPERTY()
		class TSubclassOf<class UWidget_EnemyBossTitle> m_pInst_TitleWidget;

	UPROPERTY()
		class UWidget_EnemyBossTitle* m_pTitleWidget;

public:	
	UCpt_EnemyBossHp();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddHeart(int32 nHp);
	void SetHpStart();

	void SetHeartPosition(FVector2D vPos, float fSize);

	void SetHit();
	void SetDestroy();
};
