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
		class UCpt_CamAction* m_pRoot;	//! �θ� Compoennt �����ͺ���

	bool m_bActive = false;	//! �׼� Ȱ��ȭ üũ ����
	bool m_bLife = false;	//! �׼� ��� ����(Active�� ������ Life�� false���Ǹ� �׼��� ���� ����)

public:
	//! �ʱ�ȭ
	virtual void Init(class UCpt_CamAction* pRoot);

	//! �Ҹ���
	virtual void Destroy();

	//! �׼� Ȱ��ȭ
	virtual void ActiveAction();

	//! �׼� ��Ȱ��ȭ
	virtual void DeActiveAction();

	//! �׼� Update
	virtual void Tick_Action(float fDeltaTime);

	bool GetActive() { return m_bActive; }
	bool GetLife() { return m_bLife; }
};
