#include "CamAction_Evasion.h"
#include "../Cpt_CamAction.h"
#include "Kismet/KismetMathLibrary.h"

void UCamAction_Evasion::ActiveAction()
{
	m_vOriginCamPos = m_pRoot->GetCamera_OriPos();
	m_rOriginCamRota = m_pRoot->GetCamera_OriRota();

	m_fOrigin_Length = m_pRoot->GetSpringArm()->TargetArmLength;
	m_fResult_Length = 550.0f;

	m_bAimComp = false;
	m_bActive = true;
	m_bLife = true;
	m_pRoot->SetMouseLock(true);
	m_fCurrTime = 0.0f;
}

void UCamAction_Evasion::DeActiveAction()
{
	m_bAimComp = false;
	m_bActive = false;

	m_pRoot->SetMouseLock(false);
}

void UCamAction_Evasion::Tick_Action(float fDeltaTime)
{
	if (m_bLife == false) return;
	if (m_bActive == true)
	{
		if (m_bAimComp == false)
		{
			float fCurrentLength = m_pRoot->GetSpringArm()->TargetArmLength;
			float fInterLegth = UKismetMathLibrary::FInterpTo(fCurrentLength, m_fResult_Length, fDeltaTime, m_fInterpSpeed*2.0f);
			m_pRoot->GetSpringArm()->TargetArmLength = fInterLegth;

			if (FMath::Abs(fCurrentLength - m_fResult_Length) < 5.0f)
			{
				m_pRoot->GetSpringArm()->TargetArmLength = m_fResult_Length;
				m_bAimComp = true;
				//DeActiveAction();
			}
		}
		else
		{
			m_fCurrTime += fDeltaTime;
			if (m_fCurrTime > m_fAgoTime)
			{
				DeActiveAction();
				m_fCurrTime = 0.0f;
			}
		}
	}
	else
	{
		float fCurrentLength = m_pRoot->GetSpringArm()->TargetArmLength;
		float fInterLegth = UKismetMathLibrary::FInterpTo(fCurrentLength, m_fOrigin_Length, fDeltaTime, m_fInterpSpeed);
		m_pRoot->GetSpringArm()->TargetArmLength = fInterLegth;

		if (FMath::Abs(fCurrentLength - m_fOrigin_Length) < 5.0f)
		{
			m_pRoot->GetSpringArm()->TargetArmLength = m_fOrigin_Length;
			m_bLife = false;
		}
	}
}