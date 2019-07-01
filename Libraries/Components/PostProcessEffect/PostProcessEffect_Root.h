// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "PostProcessEffect_Root.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REVENGER_API UPostProcessEffect_Root : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PostProcessMaterial, Meta = (AllowPrivateAccess = true))
		class UMaterialInterface* m_pInstance_Material;		//! Blueprint������ �Է��� Material ����� ����

	UPROPERTY()
		class UMaterialInstanceDynamic* m_pDynamicMaterial;	//! InstanceDynamic���� �����, �� ������ ����ؼ� ���׸��� ���η� ������

	UPROPERTY()
		class UPostProcessComponent* m_pPostProcess;	//! ����Ʈ�� ������ PostProcess �����ͺ���

	bool m_bActive = false;
	bool m_bInit = false;

public:
	UPostProcessEffect_Root();
	~UPostProcessEffect_Root();

	//! �ʱ�ȭ
	//! UPostProcessComponent* pPostProcessComponent : ����Ʈ ������ PostProcess ������ �ޱ�
	//! UObject* WorldContextObject : World Actor �ޱ�(GetWorld())
	virtual void Init(class UPostProcessComponent* pPostProcessComponent, UObject* WorldContextObject);

	//! ����Ʈ Ȱ��ȭ
	virtual void Enter();

	//! ����Ʈ Update
	virtual bool Tick_Effect(float fDeltaTime);

	//! ����Ʈ ��Ȱ��ȭ
	virtual void End();


};
