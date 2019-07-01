// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Die.h"
#include "Actor/Characters/GameCharacter.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Libraries/Components/SlowMotion/Cpt_SlowMotion.h"
#include "Libraries/Components/PostProcessEffect/Cpt_PostProcessEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MouseMng/Cpt_MouseLandMng.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"

void UState_GBox_Die::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_Die::Enter()
{
	Super::Enter();
	GetRootChar()->DestroyShield();

	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Die"), 1.0f, TEXT("Start"));	
	GetRootChar()->Tags.Empty();
	GetRootChar()->Tags.Add(TEXT("PlayerDie"));

	//ULOG(TEXT("Die tag : %s"), *GetRootChar()->Tags);

	GetRootChar()->GetSlowMotion()->Active_SlowMotion(1000.0f, 0.5f, 2.0f);	
	GetRootChar()->GetPostProcessEffect()->Active_Effect(TEXT("Gray"));
	GetRootChar()->SetLife(false);

	m_fDieTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	FRotator vLook = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), m_vHitDirection);
	vLook.Pitch = 0.0f;
	vLook.Roll = 0.0f;
	GetRootChar()->SetActorRotation(vLook);

	GetRootChar()->GetMouseMng()->SetMouseCamMove(false);
	m_bKeyInput = false;
}

void UState_GBox_Die::Exit()
{
	Super::Exit();
}

void UState_GBox_Die::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	float fSpeed = UKismetMathLibrary::FInterpTo(GetRootChar()->GetSpringArm()->TargetArmLength, 600.0f, fDeltaTime, 0.45f);
	GetRootChar()->GetSpringArm()->TargetArmLength = fSpeed;

	if (m_bKeyInput == false)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fDieTime >= 0.5f)
		{
			ULOG(TEXT("End KeyInput OK"));
			m_bKeyInput = true;
		}
	}

	if (m_bKeyInput == true)
	{
		if (GetRootChar()->GetKeyStateMng()->GetAnyKeyIsDown() == true)
		{
			UGameplayStatics::OpenLevel(GetRootChar()->GetWorld(), TEXT("Loading_Game"), true);
			return;
		}

		if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftMouseButton) == true)
		{
			UGameplayStatics::OpenLevel(GetRootChar()->GetWorld(), TEXT("Loading_Game"), true);
			return;
		}
	}
	//m_fDieTime += fDeltaTime;
	//if (m_fDieTime > 0.8f)
	//{
	//	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftMouseButton) == true)
	//	{
	//		//UGameplayStatics::OpenLevel(GetRootChar()->GetWorld(), FName(*GetRootChar()->GetWorld()->GetMapName()), true);
	//		UGameplayStatics::OpenLevel(GetRootChar()->GetWorld(), TEXT("Stage_1"), true);
	//	}
	//}

	//m_fSpringArm = FMath::Lerp(m_fSpringArm, GetRootChar()->GetSpringArm()->TargetArmLength - 1000.0f, 5.0f * fDeltaTime);
	//GetRootChar()->GetSpringArm()->TargetArmLength = m_fSpringArm;


	if (m_bMotionEnd == true)
	{
		GetRootChar()->Destroy();
		return;
	}

}

void UState_GBox_Die::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
	if (StateMessage == "Dist")
	{
		GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Disint);
	}
}
