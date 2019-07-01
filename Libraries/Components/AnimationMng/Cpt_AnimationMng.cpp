// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_AnimationMng.h"

#include "GameFramework/Character.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Mdl_AnimationStiffen.h"
#include "Res_AnimationList.h"

UCpt_AnimationMng::UCpt_AnimationMng()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_AnimationMng::BeginPlay()
{
	Super::BeginPlay();

	m_pCharacter = Cast<ACharacter>(GetOwner());
	if (m_pCharacter == nullptr)
	{
		ULOG(TEXT("Pawn is NULL"));
		return;
	}

	m_pAnimInstance = m_pCharacter->GetMesh()->GetAnimInstance();
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance Is null"));
		return;
	}
	APawn* pPawn = m_pAnimInstance->TryGetPawnOwner();
	if (pPawn == nullptr)
	{
		ULOG(TEXT("Pawn Is null"));
		return;
	}

	m_pModule_Stiffen = NewObject<UMdl_AnimationStiffen>();
	m_pModule_Stiffen->Init(m_pAnimInstance);

	for (TMap<FString, UAnimSequenceBase*>::TIterator it = m_pListSave_Sequence_R.CreateIterator(); it; ++it)
	{
		m_pAnimList_Sequence_R.Add(it->Key, it->Value);
	}

	for (TMap<FString, UAnimMontage*>::TIterator it = m_pListSave_Montage.CreateIterator(); it; ++it)
	{
		m_pAnimList_Montage.Add(it->Key, it->Value);
	}
}

void UCpt_AnimationMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (m_pModule_Stiffen != nullptr)
	{
		m_pModule_Stiffen->ConditionalBeginDestroy();
		m_pModule_Stiffen = nullptr;
	}

	m_pCharacter = nullptr;
	m_pAnimInstance = nullptr;
}

void UCpt_AnimationMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_pModule_Stiffen != nullptr) m_pModule_Stiffen->Tick_Stiffen(DeltaTime);
}

void UCpt_AnimationMng::AddAnimList(class URes_AnimationList* pAnimList)
{
	TMap<FString, class UAnimSequenceBase*> pSequenceList = pAnimList->GetAnimList_Sequence();
	TMap<FString, class UAnimMontage*> pMontageList = pAnimList->GetAnimList_Montage();

	m_pListSave_Montage = pMontageList;
	m_pListSave_Sequence_R = pSequenceList;
}

void UCpt_AnimationMng::SetAnimList(FString sPath)
{
	FText TextVariable = FText::AsCultureInvariant(sPath);
	ConstructorHelpers::FClassFinder<URes_AnimationList> Const_AnimList(*sPath);
	if (Const_AnimList.Succeeded())
	{
		URes_AnimationList* pAnimList = Const_AnimList.Class->GetDefaultObject<URes_AnimationList>();
		AddAnimList(pAnimList);
	}
}

float UCpt_AnimationMng::PlayAnimationMontage(FString sMtgName, float InPlayRate, FName StartSectionName)
{
	if (m_pCharacter == nullptr) return -1.0f;

	UAnimMontage* pAnimation = GetAnimation_Montage(sMtgName);
	if (pAnimation == nullptr) return -1.0f;
	float fTime = m_pCharacter->PlayAnimMontage(pAnimation, InPlayRate, StartSectionName);
	return fTime * (1.0f / InPlayRate);
}

float UCpt_AnimationMng::PlayAnimationSequnceBase(FString sAniName, FString sSlotName, float fBlendInTime, float fBlendOutTIme, float fPlayRate)
{
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is null"));
		return -1.0f;
	}
	UAnimSequenceBase* pAnimation = GetAnimation_Sequence(sAniName);
	if (pAnimation == nullptr)
	{
		ULOG(TEXT("Animation  is null"));
		return -1.0f;
	}

	UAnimMontage* pAnimationMtg = m_pAnimInstance->PlaySlotAnimationAsDynamicMontage(pAnimation, FName(*sSlotName), fBlendInTime, fBlendOutTIme, fPlayRate);
	float fTime = m_pCharacter->PlayAnimMontage(pAnimationMtg, fPlayRate);

	return fTime * (1.0f / fPlayRate);
}


UAnimMontage* UCpt_AnimationMng::GetAnimation_Montage(FString sName)
{
	for (TMap<FString, UAnimMontage*>::TIterator it = m_pAnimList_Montage.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			return it->Value;
		}
	}
	return nullptr;
}

UAnimSequenceBase* UCpt_AnimationMng::GetAnimation_Sequence(FString sName)
{
	for (TMap<FString, UAnimSequenceBase*>::TIterator it = m_pAnimList_Sequence_R.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			return it->Value;
		}
	}
	return nullptr;
}


void UCpt_AnimationMng::StopAnimation_Montage(FString sName)
{
	if (m_pCharacter == nullptr) return;
	UAnimMontage* pAnimation = GetAnimation_Montage(sName);
	if (pAnimation == nullptr) return;
	m_pCharacter->StopAnimMontage(pAnimation);
}

void UCpt_AnimationMng::StopAnimation_SequnceBaseSlot(FString sName, float fBlendTime)
{
	if (m_pAnimInstance == nullptr) return;
	m_pAnimInstance->StopSlotAnimation(fBlendTime, FName(*sName));
}

void UCpt_AnimationMng::Active_Stiffen(float fTime, float fStiffenScale)
{
	if (m_pModule_Stiffen == nullptr) return;

	m_pModule_Stiffen->Active_Stiffen(fTime, fStiffenScale);
}
