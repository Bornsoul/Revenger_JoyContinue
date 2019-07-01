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
		class UMaterialInterface* m_pInstance_Material;		//! Blueprint내에서 입력한 Material 저장용 변수

	UPROPERTY()
		class UMaterialInstanceDynamic* m_pDynamicMaterial;	//! InstanceDynamic변수 저장용, 이 변수를 사용해서 마테리얼 내부로 접근함

	UPROPERTY()
		class UPostProcessComponent* m_pPostProcess;	//! 이펙트를 적용할 PostProcess 포인터변수

	bool m_bActive = false;
	bool m_bInit = false;

public:
	UPostProcessEffect_Root();
	~UPostProcessEffect_Root();

	//! 초기화
	//! UPostProcessComponent* pPostProcessComponent : 이펙트 적용할 PostProcess 포인터 받기
	//! UObject* WorldContextObject : World Actor 받기(GetWorld())
	virtual void Init(class UPostProcessComponent* pPostProcessComponent, UObject* WorldContextObject);

	//! 이펙트 활성화
	virtual void Enter();

	//! 이펙트 Update
	virtual bool Tick_Effect(float fDeltaTime);

	//! 이펙트 비활성화
	virtual void End();


};
