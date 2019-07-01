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
		TMap<FString, class UAnimMontage*> m_pAnimList_Montage;	//! Ŭ�������� ����ϴ� ���� �ִϸ��̼� ����Ʈ
	UPROPERTY()
		TMap<FString, class UAnimSequenceBase*> m_pAnimList_Sequence_R; //! Ŭ�������� ����ϴ� ���� �ִϸ��̼� ����Ʈ

	UPROPERTY()
		TMap<FString, class UAnimMontage*> m_pListSave_Montage;		//! UAnimationList�� �ִϸ��̼� ����Ʈ ������ ����
	UPROPERTY()
		TMap<FString, class UAnimSequenceBase*> m_pListSave_Sequence_R; //! UAnimationList�� �ִϸ��̼� ����Ʈ ������ ����

	UPROPERTY()
		class UAnimInstance* m_pAnimInstance;	//! �θ� ĳ������ AnimInstance ������ ����

	UPROPERTY()
		class ACharacter* m_pCharacter;		//! �θ� ĳ���� ������ ����

	UPROPERTY()
		class UMdl_AnimationStiffen* m_pModule_Stiffen;	//! ���� ��� Ŭ����

private:
	void AddAnimList(class URes_AnimationList* pAnimList);

public:
	UCpt_AnimationMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! �ִϸ��̼� ����Ʈ BP �ҷ�����
	//! FString sPath : UAnimationList Blueprint�� ��θ� �Է��Ѵ�
	void SetAnimList(FString sPath);

	//! Montage�ִϸ��̼� ���
	//! FString sMtgName : UAnimationList�� ��ϵ� �ִϸ��̼� �̸�
	//! float InPlayRate : ��� �ӵ�(1.0f �������� �ӵ�)
	//! FName StartSectionName : Montage���� Section�̸�
	//! return : �ִϸ��̼� ��� �� �ð� ��ȯ
	float PlayAnimationMontage(FString sMtgName, float InPlayRate = 1.0, FName StartSectionName = NAME_None);

	//! �Ϲ� �ִϸ��̼� ���
	//! FString sAniName : UAnimationList�� ��ϵ� �ִϸ��̼� �̸�
	//! FString sSlotName : �ִϸ��̼� ��� Slot ����(�� : DefaultSlot)
	//! float fBlendInTime : Blend In �ð� ���� (�ִϸ��̼� ��� ����)
	//! float fBlendOutTime : Blend Out �ð� ���� (�ִϸ��̼� ���� ����)
	//! float fPlayRate : ��� �ӵ�(1.0f �������� �ӵ�)
	//! return : �ִϸ��̼� ��� �� �ð� ��ȯ
	float PlayAnimationSequnceBase(FString sAniName, FString sSlotName, float fBlendInTime = 0.1f, float fBlendOutTIme = 0.1f, float fPlayRate = 1.0f);

	//! UAnimationList�� ��ϵ� Montage ã�Ƽ� ��ȯ
	class UAnimMontage* GetAnimation_Montage(FString sName);

	//! UAnimationList�� ��ϵ� �ִϸ��̼� ã�Ƽ� ��ȯ
	class UAnimSequenceBase* GetAnimation_Sequence(FString sName);

	//! Montage�ִϸ��̼� ���߱�
	void StopAnimation_Montage(FString sName);

	//! �ִϸ��̼� Slot���� ��� ���� �ִϸ��̼� ���߱�
	void StopAnimation_SequnceBaseSlot(FString sName, float fBlendTime = 0.25f);

public:
	//! �ִϸ��̼� ����(���ο� ���)
	//! float fTime : ����(���ο� ���) ���� �ð�
	//! float fStiffenScale : ��������(���ڰ� ���� ���� ���ο����� �������� ����ó�� ����)
	void Active_Stiffen(float fTime, float fStiffenScale);

};
