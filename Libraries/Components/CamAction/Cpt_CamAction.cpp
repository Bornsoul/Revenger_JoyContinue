#include "Cpt_CamAction.h"
#include "CamAction_Root.h"

#include "Actions/CamAction_Evasion.h"
#include "Actions/CamAction_Parring.h"

UCpt_CamAction::UCpt_CamAction()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_CamAction::Init(USpringArmComponent* pSpringArm, UCameraComponent* pCamera)
{
	m_pSpringArm = pSpringArm;
	m_pCamera = pCamera;

	m_vOriginCamPos = m_pCamera->GetRelativeTransform().GetLocation();
	m_rOriginCamRota = m_pCamera->GetRelativeTransform().GetRotation().Rotator();

	m_bInit = true;
}

void UCpt_CamAction::BeginPlay()
{
	Super::BeginPlay();
	m_pCharacter = Cast<ACharacter>(GetOwner());


	m_pActiveCamAction = nullptr;

	for (int i = 0; i < (int)E_CamAction::E_MAX; i++)
	{
		m_pActionClasses[i] = nullptr;
	}

	m_pActionClasses[(int)E_CamAction::E_Evasion] = NewObject<UCamAction_Evasion>();
	m_pActionClasses[(int)E_CamAction::E_Parring] = NewObject<UCamAction_Parring>();

	/*m_pActionClasses[(int)E_CamAction::E_ThrowAim] = NewObject<UCamAction_ThrowAim>();
	m_pActionClasses[(int)E_CamAction::E_SpAttack] = NewObject<UCamAction_SpAttack>();
	m_pActionClasses[(int)E_CamAction::E_DodgeAttack] = NewObject<UCamAction_DodgeAttack>();
	m_pActionClasses[(int)E_CamAction::E_Parring] = NewObject<UCamAction_Parring>();
	m_pActionClasses[(int)E_CamAction::E_Blink] = NewObject<UCamAction_Blink>();
	m_pActionClasses[(int)E_CamAction::E_BlinkAttack] = NewObject<UCamAction_BlinkAttack>();
	*/


	for (int i = 0; i < (int)E_CamAction::E_MAX; i++)
	{
		m_pActionClasses[i]->Init(this);
	}

}

void UCpt_CamAction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pSpringArm = nullptr;
	m_pCamera = nullptr;
	m_pCharacter = nullptr;

	m_pActiveCamAction = nullptr;

	for (int i = 0; i < (int)E_CamAction::E_MAX; i++)
	{
		if (m_pActionClasses[i] != nullptr) m_pActionClasses[i]->Destroy();
		m_pActionClasses[i] = nullptr;
	}
}

void UCpt_CamAction::ActiveAction(E_CamAction eAction)
{
	if (m_bInit == false) return;

	//if (m_pActiveCamAction != nullptr)
	//{
	//	//	return;
	//}

	UCamAction_Root* pAction = GetActionClass(eAction);
	if (pAction == nullptr) return;
	m_pActiveCamAction = pAction;
	m_pActiveCamAction->ActiveAction();
}

void UCpt_CamAction::DeActiveAction()
{
	if (m_pActiveCamAction == nullptr) return;
	m_pActiveCamAction->DeActiveAction();
}

void UCpt_CamAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pActiveCamAction != nullptr)
	{
		m_pActiveCamAction->Tick_Action(DeltaTime);
		if (m_pActiveCamAction->GetLife() == false)
		{
			m_pActiveCamAction = nullptr;
		}
	}
}

void UCpt_CamAction::CamResetToForward()
{
	if (m_pCharacter == nullptr)
	{
		ULOG(TEXT("Error_Character is nullptr"));
		return;
	}

	FRotator pCam = GetCamResetToForwardRotator();
	m_pCharacter->GetController()->SetControlRotation(pCam);
}

FRotator UCpt_CamAction::GetCamResetToForwardRotator()
{
	if (m_pCharacter == nullptr)
	{
		ULOG(TEXT("Error_Character is nullptr"));
		return FRotator::ZeroRotator;
	}

	FRotator pCam = m_pCharacter->GetController()->GetControlRotation();
	pCam.Roll = 0.0f;
	pCam.Pitch = 0.0f;
	pCam.Yaw = m_pCharacter->GetCapsuleComponent()->GetComponentRotation().Yaw;

	return pCam;
}

UCamAction_Root * UCpt_CamAction::GetActionClass(E_CamAction eFindState)
{
	return m_pActionClasses[(int)eFindState];
}
