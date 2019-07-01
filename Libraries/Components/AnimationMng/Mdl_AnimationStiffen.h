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

	//! �ʱ�ȭ �Լ�
	//! UAnimInstance* pAnimInstance : AnimMng_Component���� ������ AnimInstace�� ���� ������ �ִ´�.
	void Init(class UAnimInstance* pAnimInstance);

	//! ����ȿ�� Ȱ��ȭ
	//! float fTime : ���� ���� �ð�
	//! float fStiffenScale = ���� ����(���ڰ� ���� ���� ���ο� ����� ���� ������)
	void Active_Stiffen(float fTime, float fStiffenScale = 0.001f);

	//! Update �Լ� : Ȱ��ȭ�� ����ȿ�� �ð� �� ȿ�� Update�Ѵ�.
	void Tick_Stiffen(float DeltaTime);

};
