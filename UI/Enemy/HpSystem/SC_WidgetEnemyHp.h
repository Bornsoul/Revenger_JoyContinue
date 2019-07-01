// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/SceneComponent.h"
#include "SC_WidgetEnemyHp.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API USC_WidgetEnemyHp : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* m_pBox;

	UPROPERTY(EditAnywhere)
		TArray<class UWidgetComp_EnemyHp*> m_pEnemyHp;

	UPROPERTY()
		class UWidgetComp_EnemyHp* m_pEnemy;

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpPos = FVector2D(30.0f, 250.0f);

	bool m_bActive = false;
	int nCnt = 0;

public:
	USC_WidgetEnemyHp();

public:
	virtual void BeginPlay() override;

	void SetInit(int nCnt);
	void Tick_Transform(FVector vLocation, float fDeltaTime);
	void SetHit();
	void SetDestroy();
};
