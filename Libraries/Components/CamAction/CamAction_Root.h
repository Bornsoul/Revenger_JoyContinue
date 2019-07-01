// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "CamAction_Root.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UCamAction_Root : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UCpt_CamAction* m_pRoot;	//! 부모 Compoennt 포인터변수

	bool m_bActive = false;	//! 액션 활성화 체크 변수
	bool m_bLife = false;	//! 액션 목숨 변수(Active와 별도로 Life가 false가되면 액션이 완전 종료)

public:
	//! 초기화
	virtual void Init(class UCpt_CamAction* pRoot);

	//! 소멸자
	virtual void Destroy();

	//! 액션 활성화
	virtual void ActiveAction();

	//! 액션 비활성화
	virtual void DeActiveAction();

	//! 액션 Update
	virtual void Tick_Action(float fDeltaTime);

	bool GetActive() { return m_bActive; }
	bool GetLife() { return m_bLife; }
};
