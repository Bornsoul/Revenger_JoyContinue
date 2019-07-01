// Fill out your copyright notice in the Description page of Project Settings.

#include "Mdl_AnimationStiffen.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

UMdl_AnimationStiffen::UMdl_AnimationStiffen()
{

}

UMdl_AnimationStiffen::~UMdl_AnimationStiffen()
{
	m_pAnimInstance = nullptr;
	m_pCharacter = nullptr;
}

void UMdl_AnimationStiffen::Init(class UAnimInstance* pAnimInstance)
{
	m_pAnimInstance = pAnimInstance;
	if (m_pAnimInstance == nullptr) return;
	m_pCharacter = Cast<ACharacter>(m_pAnimInstance->TryGetPawnOwner());
	m_bInit = true;
}

void UMdl_AnimationStiffen::Active_Stiffen(float fTime, float fStiffenScale)
{
	if (m_bInit == false) return;
	m_bIsStiffen = true;
	m_fAgoStiffenTime = fTime;
	m_fCurrStiffenTime = 0.0f;
	m_pCharacter->GetMesh()->GlobalAnimRateScale = fStiffenScale;

	m_bIsStiffen = true;
}

void UMdl_AnimationStiffen::Tick_Stiffen(float DeltaTime)
{
	if (m_bInit == false) return;
	if (m_bIsStiffen == false) return;

	m_fCurrStiffenTime += DeltaTime;
	if (m_fCurrStiffenTime > m_fAgoStiffenTime)
	{
		m_pCharacter->GetMesh()->GlobalAnimRateScale = 1.0f;
		m_bIsStiffen = false;
		return;
	}

	m_pAnimInstance->UpdateAnimation(DeltaTime * m_pCharacter->GetMesh()->GlobalAnimRateScale, true);
}


