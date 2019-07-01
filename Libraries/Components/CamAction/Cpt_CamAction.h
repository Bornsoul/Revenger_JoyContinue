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
	//! 기본 캠 좌표, 회전 저장 변수
	FVector	 m_vOriginCamPos;
	FRotator m_rOriginCamRota;

	bool m_bInit = false;

	//! 마우스 움직임 잠금 토글
	bool m_bMouseLock = false;

public:
	UCpt_CamAction();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//! 초기화 함수, 플레이어 캐릭터 클래스의 SpringArm과 Camera를 세팅)
	void Init(USpringArmComponent* pSpringArm, UCameraComponent* pCamera);

	//! 캠액션 실행
	void ActiveAction(E_CamAction eAction);

	//! 캠액션 종료
	void DeActiveAction();

	//! 캠의 회전값을 최초 값으로 리셋함
	void CamResetToForward();

	//! 캠의 최초 회전값 가져오기
	FRotator GetCamResetToForwardRotator();


	//! SpringArm, Camera 변수 포인터 받아오기
	USpringArmComponent* GetSpringArm() { return m_pSpringArm; }
	UCameraComponent* GetCamera() { return m_pCamera; }

	//! 최초 카메라 좌표, 회전값 가져오기
	FVector GetCamera_OriPos() { return m_vOriginCamPos; }
	FRotator GetCamera_OriRota() { return m_rOriginCamRota; }

	//! 마우스 움직임 잠그기(m_bMouseLock변수 검사로 플레이어 클래스에서 마우스 움직일지 판단)
	void SetMouseLock(bool bLock) { m_bMouseLock = bLock; }

	//! 마우스 Lock상태 받아오기
	bool GetIsMouseLock() { return m_bMouseLock; }

	//! 캠액션 클래스 받아오기
	class UCamAction_Root* GetActionClass(E_CamAction eFindState);

	ACharacter* GetCharacter() { return m_pCharacter; }
};
