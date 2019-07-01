// Fill out your copyright notice in the Description page of Project Settings.

#include "Cloud.h"
#include "UI/Dialog/Cpt_WidgetDialog.h"
#include "UI/GameHUD/Widget/StageIntroText/Cpt_StageIntro.h"

#include "Actor/Characters/Player/GBox/GBox.h"

#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));
	m_pDialog = CreateDefaultSubobject <UCpt_WidgetDialog>(TEXT("Dialogs"));
	m_pStageIntro = CreateDefaultSubobject<UCpt_StageIntro>(TEXT("StageIntros"));


}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();

	/*if (m_pDialog != nullptr)
	{
		m_pDialog->AddDialogList(m_pInst_Dialog);
	}*/
	
	m_bStart = false;
	m_fStartTime_Curr = 0.0f;
	if (m_pDialog != nullptr)
	{
		m_pDialog->InitDialog();
	}


	m_bDestroy = false;
}
void ACloud::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pDialog != nullptr)
	{
		m_pDialog->DestroyComponent();
		m_pDialog = nullptr;		
	}

	if (m_pStageIntro != nullptr)
	{
		m_pStageIntro->DestroyComponent();
		m_pStageIntro = nullptr;
	}
	
	m_pPlayer = nullptr;
}

void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (m_pDialog == nullptr) return;
	if (m_pStageIntro->GetIsPlaying() == true)return;

	if (m_bFindPlayer == false)
	{
		AGBox* pPlayer = Cast<AGBox>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (pPlayer != nullptr)
		{
			//ULOG(TEXT("Find Player : %s"), *pPlayer->GetName());
			m_pPlayer = pPlayer;
			m_pPlayer->SetMovement(false);

			if (m_pStageIntro != nullptr)
			{
				m_pStageIntro->SetInit();
				m_pStageIntro->SetPlay(m_vStartEndTime.X, m_vStartEndTime.Y);
			}

			m_bFindPlayer = true;
		}
	}
	
	if (m_pPlayer == nullptr) return;
	if (m_bDestroy == false)
	{
		if (m_bStart == false)
		{
			m_fStartTime_Curr += DeltaTime;
			if (m_fStartTime_Curr >= m_fStartTime_End)
			{
				m_fStartTime_Curr = 0.0f;

				DialogStart();
				m_bStart = true;
			}
		}
		else
		{
			m_fStartTime_Curr += DeltaTime;

			if (m_fStartTime_Curr >= 0.3f)
			{
				if (m_pKeyStateMng->GetKeyIsJustRelease(EKeys::SpaceBar) ||
					m_pKeyStateMng->GetKeyIsJustRelease(EKeys::LeftMouseButton))
				{					
					m_fStartTime_Curr = 0.0f;
					DialogStart();
					return;
				}
			}
		}
	}
	else
	{
		m_fStartTime_Curr += DeltaTime;

		if (m_fStartTime_Curr >= 1.0f)
		{
			m_fStartTime_Curr = 0.0f;
			Destroy();
		}
	}
	
}

void ACloud::DialogStart()
{
	if (m_pDialog->GetIsTyping())
	{
		m_pDialog->SkipDialog();
		return;
	}

	bool bDialog = m_pDialog->PlayDialog(m_nDialogGroup, m_nDialogIndex);
	if (bDialog == false)
	{
		if (m_pPlayer != nullptr)
		{
			m_pPlayer->SetMovement(true);
		}

		m_bDestroy = true;
		m_fStartTime_Curr = 0.0f;
		ULOG(TEXT("Destroy Dialog"));
		return;
	}
	m_nDialogIndex++;

}