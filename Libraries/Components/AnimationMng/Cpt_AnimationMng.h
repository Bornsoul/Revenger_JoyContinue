// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_AnimationMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_AnimationMng : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TMap<FString, class UAnimMontage*> m_pAnimList_Montage;	//! 클래스에서 운용하는 실제 애니메이션 리스트
	UPROPERTY()
		TMap<FString, class UAnimSequenceBase*> m_pAnimList_Sequence_R; //! 클래스에서 운용하는 실제 애니메이션 리스트

	UPROPERTY()
		TMap<FString, class UAnimMontage*> m_pListSave_Montage;		//! UAnimationList의 애니메이션 리스트 포인터 변수
	UPROPERTY()
		TMap<FString, class UAnimSequenceBase*> m_pListSave_Sequence_R; //! UAnimationList의 애니메이션 리스트 포인터 변수

	UPROPERTY()
		class UAnimInstance* m_pAnimInstance;	//! 부모 캐릭터의 AnimInstance 포인터 변수

	UPROPERTY()
		class ACharacter* m_pCharacter;		//! 부모 캐릭터 포인터 변수

	UPROPERTY()
		class UMdl_AnimationStiffen* m_pModule_Stiffen;	//! 경직 모듈 클래스

private:
	void AddAnimList(class URes_AnimationList* pAnimList);

public:
	UCpt_AnimationMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! 애니메이션 리스트 BP 불러오기
	//! FString sPath : UAnimationList Blueprint의 경로를 입력한다
	void SetAnimList(FString sPath);

	//! Montage애니메이션 재생
	//! FString sMtgName : UAnimationList에 등록된 애니메이션 이름
	//! float InPlayRate : 재생 속도(1.0f 오리지날 속도)
	//! FName StartSectionName : Montage내부 Section이름
	//! return : 애니메이션 재생 총 시간 반환
	float PlayAnimationMontage(FString sMtgName, float InPlayRate = 1.0, FName StartSectionName = NAME_None);

	//! 일반 애니메이션 재생
	//! FString sAniName : UAnimationList에 등록된 애니메이션 이름
	//! FString sSlotName : 애니메이션 재생 Slot 설정(예 : DefaultSlot)
	//! float fBlendInTime : Blend In 시간 설정 (애니메이션 재생 블랜드)
	//! float fBlendOutTime : Blend Out 시간 설정 (애니메이션 종료 블랜드)
	//! float fPlayRate : 재생 속도(1.0f 오리지날 속도)
	//! return : 애니메이션 재생 총 시간 반환
	float PlayAnimationSequnceBase(FString sAniName, FString sSlotName, float fBlendInTime = 0.1f, float fBlendOutTIme = 0.1f, float fPlayRate = 1.0f);

	//! UAnimationList에 등록된 Montage 찾아서 반환
	class UAnimMontage* GetAnimation_Montage(FString sName);

	//! UAnimationList에 등록된 애니메이션 찾아서 반환
	class UAnimSequenceBase* GetAnimation_Sequence(FString sName);

	//! Montage애니메이션 멈추기
	void StopAnimation_Montage(FString sName);

	//! 애니메이션 Slot에서 재생 중인 애니메이션 멈추기
	void StopAnimation_SequnceBaseSlot(FString sName, float fBlendTime = 0.25f);

public:
	//! 애니메이션 경직(슬로우 모션)
	//! float fTime : 경직(슬로우 모션) 유지 시간
	//! float fStiffenScale : 경직강도(숫자가 낮을 수록 슬로우모션이 강해져서 경직처럼 보임)
	void Active_Stiffen(float fTime, float fStiffenScale);

};
