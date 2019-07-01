// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_CamAction.generated.h"

UENUM()
enum class E_CamAction : uint8
{
	E_Evasion UMETA(DisplayName = "Evasion"),
	E_Parring UMETA(DisplayName = "Parring"),

	E_MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_CamAction : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		USpringArmComponent*	 m_pSpringArm;

	UPROPERTY()
		UCameraComponent*		 m_pCamera;

	UPROPERTY()
		ACharacter*				 m_pCharacter;

private:
	UPROPERTY()
		class UCamAction_Root*	m_pActiveCamAction;

	UPROPERTY()
		class UCamAction_Root*	m_pActionClasses[(int)E_CamAction::E_MAX];

private:
	//! �⺻ ķ ��ǥ, ȸ�� ���� ����
	FVector	 m_vOriginCamPos;
	FRotator m_rOriginCamRota;

	bool m_bInit = false;

	//! ���콺 ������ ��� ���
	bool m_bMouseLock = false;

public:
	UCpt_CamAction();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//! �ʱ�ȭ �Լ�, �÷��̾� ĳ���� Ŭ������ SpringArm�� Camera�� ����)
	void Init(USpringArmComponent* pSpringArm, UCameraComponent* pCamera);

	//! ķ�׼� ����
	void ActiveAction(E_CamAction eAction);

	//! ķ�׼� ����
	void DeActiveAction();

	//! ķ�� ȸ������ ���� ������ ������
	void CamResetToForward();

	//! ķ�� ���� ȸ���� ��������
	FRotator GetCamResetToForwardRotator();


	//! SpringArm, Camera ���� ������ �޾ƿ���
	USpringArmComponent* GetSpringArm() { return m_pSpringArm; }
	UCameraComponent* GetCamera() { return m_pCamera; }

	//! ���� ī�޶� ��ǥ, ȸ���� ��������
	FVector GetCamera_OriPos() { return m_vOriginCamPos; }
	FRotator GetCamera_OriRota() { return m_rOriginCamRota; }

	//! ���콺 ������ ��ױ�(m_bMouseLock���� �˻�� �÷��̾� Ŭ�������� ���콺 �������� �Ǵ�)
	void SetMouseLock(bool bLock) { m_bMouseLock = bLock; }

	//! ���콺 Lock���� �޾ƿ���
	bool GetIsMouseLock() { return m_bMouseLock; }

	//! ķ�׼� Ŭ���� �޾ƿ���
	class UCamAction_Root* GetActionClass(E_CamAction eFindState);

	ACharacter* GetCharacter() { return m_pCharacter; }
};
