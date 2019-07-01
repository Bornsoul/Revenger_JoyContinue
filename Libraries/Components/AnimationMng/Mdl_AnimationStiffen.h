// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Mdl_AnimationStiffen.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMdl_AnimationStiffen : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class ACharacter* m_pCharacter;

	UPROPERTY()
		class UAnimInstance* m_pAnimInstance;

	float m_fAgoStiffenTime;
	float m_fCurrStiffenTime;
	bool m_bIsStiffen = false;

	bool m_bInit = false;
public:
	UMdl_AnimationStiffen();
	~UMdl_AnimationStiffen();

	//! 초기화 함수
	//! UAnimInstance* pAnimInstance : AnimMng_Component에서 추출한 AnimInstace를 인자 값으로 넣는다.
	void Init(class UAnimInstance* pAnimInstance);

	//! 경직효과 활성화
	//! float fTime : 경직 유지 시간
	//! float fStiffenScale = 경직 강도(숫자가 낮을 수록 슬로우 모션이 더욱 느려짐)
	void Active_Stiffen(float fTime, float fStiffenScale = 0.001f);

	//! Update 함수 : 활성화된 경직효과 시간 및 효과 Update한다.
	void Tick_Stiffen(float DeltaTime);

};
