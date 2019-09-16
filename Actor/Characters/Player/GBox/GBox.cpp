// Fill out your copyright notice in the Description page of Project Settings.

#include "GBox.h"
#include "AnimInst_GBox.h"
#include "Shield.h"
#include "FootSmoke.h"
#include "Actor/Characters/Player/Stick/Stick.h"
#include "Actor/Props/FootPush/Cpt_FootPushLine.h"
#include "Actor/SaveData/Cpt_GameSave.h"
#include "Actor/SaveData/GameSaveMng.h"
#include "Actor/SaveData/Act_SpawnPoint.h"

#include "State/StateMng_GBox.h"
#include "UI/GameHUD/HUD_GameMain.h"
#include "UI/GameHUD/Widget/Widget_GameHUD.h"
#include "UI/GameHUD/Widget/Widget_PlayerDash.h"
#include "UI/GameHUD/Widget/SlowMotionGage/Cpt_SlowGage.h"
#include "UI/GameHUD/Widget/Widget_PlayerKeyInfo.h"
#include "UI/GameHUD/Widget/DieScreen/Cpt_DieScreen.h"
#include "UI/GameHUD/Widget/SimpleMenu/Cpt_SimpleMenu.h"
#include "UI/GameHUD/Widget/PuaseMenu/Cpt_PauseMenu.h"
#include "UI/ResultHUD/Cpt_ResultWidget.h"
#include "UI/GameHUD/Widget/SlowMotionGage/WidgetComp_SlowGage.h"

#include "UI/NewGameHUD/HUD_Game.h"
#include "UI/NewGameHUD/Widget_GHUD.h"
#include "UI/NewGameHUD/Widget/Widget_BulletTime/Widget_SlowGageHUD.h"
#include "UI/NewGameHUD/Widget/Widget_SkillCoolTime/Widget_SkillHUD.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/SlowMotion/Cpt_SlowMotion.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/PostProcessEffect/Cpt_PostProcessEffect.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/SlowMotion/Cpt_SlowMotion.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/MouseMng/Cpt_MouseLandMng.h"
#include "Libraries/Components/GhostTrail/Cpt_GhostTrail.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/PostProcessComponent.h"
#include "Components/ArrowComponent.h"

AGBox::AGBox()
{
	PrimaryActorTick.bCanEverTick = true;
	SetGenericTeamId(FGenericTeamId(0));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.0f, 0.f);
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->MaxAcceleration = 99999.0f;

	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	m_pSpringArm->SetupAttachment(GetMesh(), TEXT("Bip001-Spine1")); // TEXT("Bip001-Spine"));
	m_pSpringArm->bAbsoluteRotation = true;
	m_pSpringArm->TargetArmLength = 3000.f;
	m_pSpringArm->RelativeRotation = FRotator(-45.f, 45.0f, 0.0f);
	m_pSpringArm->bDoCollisionTest = false;
	m_pSpringArm->bEnableCameraLag = true;
	m_pSpringArm->CameraLagSpeed = 10.0f;

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pSpringArm, USpringArmComponent::SocketName);
	m_pCamera->bUsePawnControlRotation = false;
	m_pCamera->FieldOfView = 45.0f;

	m_pCamShake = CreateDefaultSubobject <UCpt_CamShake>(TEXT("CamShake"));
	m_pCamShake->AddCameraShakeClass(TEXT("AttackHit"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/CameraShake/BP_CamShake_AttackHit.BP_CamShake_AttackHit_C"));
	m_pCamShake->AddCameraShakeClass(TEXT("Hit"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/CameraShake/BP_CamShake_Hit.BP_CamShake_Hit_C"));

	m_pArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp1"));
	m_pArrowComp->SetupAttachment(RootComponent);

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));

	m_pPostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	m_pPostProcess->SetupAttachment(m_pCamera);

	m_pPostProcessEffect = CreateDefaultSubobject<UCpt_PostProcessEffect>(TEXT("PostProcessEffect"));
	m_pPostProcessEffect->Add_PostProcessEffect(TEXT("Hit"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/PostProcessEffect/BP_PPE_PlayerHit.BP_PPE_PlayerHit_C"));
	m_pPostProcessEffect->Add_PostProcessEffect(TEXT("Gray"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/PostProcessEffect/BP_PPE_Gray.BP_PPE_Gray_C"));
	m_pPostProcessEffect->Add_PostProcessEffect(TEXT("Chromaticblur"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/PostProcessEffect/BP_PPE_ChromaticBlur.BP_PPE_ChromaticBlur_C"));
	m_pPostProcessEffect->Add_PostProcessEffect(TEXT("SlowMotion"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/PostProcessEffect/BP_PPE_SlowMotion.BP_PPE_SlowMotion_C"));
	m_pPostProcessEffect->Add_PostProcessEffect(TEXT("HitSlash"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/PostProcessEffect/BP_PPE_SlashHit.BP_PPE_SlashHit_C"));

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitImpact.V_HitImpact'"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit_Back"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitBackWard.V_HitBackWard'"));
	m_pParticleMng->AddParticleInstance(TEXT("FootSmoke"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_SMStepSmoke.V_SMStepSmoke'"));
	m_pParticleMng->AddParticleInstance(TEXT("HitSlash"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_SlashHit.V_SlashHit'"));

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/BP_AnimList_GBox.BP_AnimList_GBox_C"));

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));
	m_pSlowMotion = CreateDefaultSubobject<UCpt_SlowMotion>(TEXT("SlowMotion"));

	m_pSoundMng = CreateDefaultSubobject<UCpt_SoundMng>(TEXT("SoundMng"));
	m_pSoundMng->Set_SoundList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/BP_SoundList_GBox.BP_SoundList_GBox_C"));

	m_pMouseLandMng = CreateDefaultSubobject<UCpt_MouseLandMng>(TEXT("MouseLandMng"));
	m_pMouseLandMng->SetupAttachment(RootComponent);

	m_pGhostTrail = CreateDefaultSubobject<UCpt_GhostTrail>(TEXT("GhostTrail"));
	m_pGhostTrail->Add_GhostTrailEffectActor(TEXT("Dash"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/GhostTrail/BP_GT_AlphaDown.BP_GT_AlphaDown_C"));
	m_pGhostTrail->Add_GhostTrailEffectActor(TEXT("SlowMotion"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/GhostTrail/BP_GT_SlowMotion.BP_GT_SlowMotion_C"));

	m_pFootPushLine = CreateDefaultSubobject<UCpt_FootPushLine>(TEXT("FootPushLine"));
	m_pFootPushLine->SetSKMesh(this);
	m_pFootPushLine->AddBone(TEXT("Bip001-L-Foot"));
	m_pFootPushLine->AddBone(TEXT("Bip001-R-Foot"));

	m_pResultWidget = CreateDefaultSubobject<UCpt_ResultWidget>(TEXT("ResultWidget"));
	m_pDieWidget = CreateDefaultSubobject<UCpt_DieScreen>(TEXT("DieScreen"));
	m_pSimpleMenu = CreateDefaultSubobject<UCpt_SimpleMenu>(TEXT("SimpleMenu"));
	m_pPauseMenu = CreateDefaultSubobject<UCpt_PauseMenu>(TEXT("PauseMenu"));

	m_pSaveMng = CreateDefaultSubobject<UCpt_GameSave>(TEXT("SaveGameMng"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Player/Joy/Animation/BP_Anim_Joy.BP_Anim_Joy_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AStick> Const_Bullet(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/Stick/BP_Stick.BP_Stick_C"));
	if (Const_Bullet.Succeeded()) m_pInstance_Stick = Const_Bullet.Class;

	static ConstructorHelpers::FClassFinder<AFootSmoke> Const_FootSmoke(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/Joy/BP_FootSmoke.BP_FootSmoke_C"));
	if (Const_FootSmoke.Succeeded()) m_pInst_FootSmoke = Const_FootSmoke.Class;
	
	static ConstructorHelpers::FClassFinder<AShield> Const_Shield(TEXT("/Game/1_Project_Main/2_Contents/Effects/Sheild/BP_Shield.BP_Shield_C"));
	if (Const_FootSmoke.Succeeded()) m_pInst_Shield = Const_Shield.Class;
	
}

void AGBox::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AGBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	

	SetActorHiddenInGame(true);
}

void AGBox::BeginPlay()
{
	Super::BeginPlay();
	GetController()->SetControlRotation(FRotator::ZeroRotator);
	
	m_pHud = Cast<AHUD_Game>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (m_pHud != nullptr)
	{
		m_pHud->Init();
	}

	//! 데이터 저장 체크
	if (m_pSaveMng->Check_DataValid() == false)
	{
		UALERT(TEXT("Error - SaveData is Empty (Player)"));		
		return;
	}

	m_nSpawnPoint = m_pSaveMng->Load_Data()->m_nSpawnPoint;
	m_nDeadCount = m_pSaveMng->Load_Data()->m_stPlayerData.m_nDeadCount;
	m_nDifficultLevel = m_pSaveMng->Load_Data()->m_nDifficulty;
	ULOG(TEXT("SpawnPoint : %d"), m_nSpawnPoint);
	ULOG(TEXT("BulletHit_Count : %d"), m_pSaveMng->Load_Data()->m_stPlayerData.m_nHitBulletCount);
	ULOG(TEXT("BulletNonHit_Count : %d"), m_pSaveMng->Load_Data()->m_stPlayerData.m_nNonHitBulletCount);
	ULOG(TEXT("DeadCount : %d"), m_nDeadCount);
	ULOG(TEXT("Difficult Level : %d"), m_nDifficultLevel);
	ULOG(TEXT("Tutorial State : %d"), m_pSaveMng->Load_Data()->m_nTutorial);	

	//! 데이터가 존재상태일때
	//! 세이브존을 한번이라도 지나쳤을때
	//! 모든 스폰지점을 확인후 세이브한곳과 같은곳을 찾아서 해당위치로 스폰시킴
	if (m_nSpawnPoint >= 0)
	{
		for (TActorIterator<AAct_SpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AAct_SpawnPoint* pObj = *ActorItr;
			if (pObj != nullptr)
			{
				if (m_nSpawnPoint == pObj->GetCurrentPoint())
				{
					SetActorLocation(pObj->GetSpawnArrow()->GetComponentLocation());
					break;
				}
			}
		}
	}

	m_pAnimInstance = Cast<UAnimInst_GBox>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)	ULOG(TEXT("AnimInstance is NULL"));

	m_pMaterialEffect->Init(GetMesh());
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Hit2);
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Disint);

	m_pPostProcessEffect->Init(m_pPostProcess);
	m_pPauseMenu->SetRoot(this);

	m_pStateMng = NewObject<UStateMng_GBox>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_Landing));
	}


	SetMovement(true);
	SetVisibleHUD(false); 
	SetAttackControl(true);
	SetSlowControl(true);
	SetDashControl(true);

	m_bLife = true;		
	m_pShield = CreateShield();	
	m_fShieldTime_End = m_fShield_ReCharge_Time;
}

void AGBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
	{
		if (m_pStateMng->IsValidLowLevel())
		{
			m_pStateMng->Destroy();
			m_pStateMng = nullptr;
		}
	}

	if (m_pShield != nullptr)
	{
		if (m_pShield->IsValidLowLevel())
		{
			m_pShield->Destroy();
			m_pShield = nullptr;
		}
	}

	if (m_pMouseLandMng != nullptr)
	{
		if (m_pMouseLandMng->IsValidLowLevel())
		{
			m_pMouseLandMng->DestroyComponent();
			m_pMouseLandMng = nullptr;
		}
	}

	if (m_pDieWidget != nullptr)
	{
		if (m_pDieWidget->IsValidLowLevel())
		{
			m_pDieWidget->DestroyComponent();
			m_pDieWidget = nullptr;
		}
	}

	if (m_pFootPushLine != nullptr)
	{
		if (m_pFootPushLine->IsValidLowLevel())
		{
			m_pFootPushLine->DestroyComponent();
			m_pFootPushLine = nullptr;
		}
	}

	if (m_pHud != nullptr)
	{
		if (m_pHud->IsValidLowLevel())
		{
			m_pHud->Destroy();
			m_pHud = nullptr;
		}
	}

	if (m_pAnimInstance != nullptr)
	{
		if (m_pAnimInstance->IsValidLowLevel())
		{
			m_pAnimInstance = nullptr;
		}
	}

	if (m_pGhostTrail != nullptr)
	{
		if (m_pGhostTrail->IsValidLowLevel())
		{
			m_pGhostTrail->DestroyComponent();
			m_pGhostTrail = nullptr;
		}
	}

	if (m_pPauseMenu != nullptr)
	{
		if (m_pPauseMenu->IsValidLowLevel())
		{
			m_pPauseMenu->DestroyComponent();			
			m_pPauseMenu = nullptr;
		}
	}

	if (m_pResultWidget != nullptr)
	{
		if (m_pResultWidget->IsValidLowLevel())
		{
			m_pResultWidget->DestroyComponent();
			m_pResultWidget = nullptr;
		}
	}

	if (m_pSaveMng != nullptr)
	{
		if (m_pSaveMng->IsValidLowLevel())
		{
			//m_pSaveMng->DestroyComponent();
			m_pSaveMng = nullptr;
		}
	}

	if (m_pSoundMng != nullptr)
	{
		if (m_pSoundMng->IsValidLowLevel())
		{
			m_pSoundMng->DestroyComponent();
			m_pSoundMng = nullptr;
		}
	}
}

void AGBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pHud != nullptr)
	{
		m_pHud->SetHudActive(m_bVisibleHUD);
	}

	PauseMenu_Tick();
	SlowGage_Tick(DeltaTime);

	if (GetMovement() == false)
	{
		AnimInst_Tick(DeltaTime);

		return;
	}
	
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Update(DeltaTime);
	}

	AnimInst_Tick(DeltaTime);
	Shield_Tick(DeltaTime);	
}

void AGBox::AnimInst_Tick(float fDeltaTime)
{
	if (m_pAnimInstance == nullptr)
	{
		return;
	}
	
	m_pAnimInstance->SetStat_Falling(GetCharacterMovement()->IsFalling());

	//! Speed
	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());	
	
	//! Direction
	float fCalcDirection = GetAnimInstance()->CalculateDirection(GetVelocity(), GetActorRotation());
	GetAnimInstance()->SetStat_MovementDirection(fCalcDirection);

	// Head, Spine 
	FVector vMouseLoc = GetMouseMng()->GetMouse_Location();
	vMouseLoc.Z = GetActorLocation().Z;
	float fLookYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), vMouseLoc).Yaw;		
	float fAngle = m_pArrowComp->GetComponentRotation().Yaw - fLookYaw; //GetArrowComponent()->GetComponentRotation().Yaw - fLookYaw;
	
	if (GetAnimInstance()->GetStat_MoveDir() == true)
	{
		// 이동중일때 (Move 상태)		
		//! 커서 방향으로 캐릭터 방향 전환
		FRotator rA = FRotator(0.0f, fLookYaw, 0.0f);
		SetActorRotation(rA);

		float fSpine = GetNormalizeDir(fAngle, GetAnimInstance()->GetRotRange_Spine().X, GetAnimInstance()->GetRotRange_Spine().Y);
		m_fSpineDirection = FMath::Lerp(m_fSpineDirection, fSpine, GetAnimInstance()->GetRotSpeed_Spine() * fDeltaTime);
		FRotator rResult_Spine = FRotator(0.0f, m_fSpineDirection, 0.0f);
		m_pAnimInstance->SetStat_SpineRotator(rResult_Spine);
	}
	else
	{
		// 가만히 있을때 (Idle 상태)
		float fHead = GetNormalizeDir(fAngle, GetAnimInstance()->GetRotRange_Head().X, GetAnimInstance()->GetRotRange_Head().Y);
		float fSpine = GetNormalizeDir(fAngle, GetAnimInstance()->GetRotRange_Spine().X, GetAnimInstance()->GetRotRange_Spine().Y);

		m_fHeadDirection = FMath::Lerp(m_fHeadDirection, fHead, GetAnimInstance()->GetRotSpeed_Head() * fDeltaTime);
		m_fSpineDirection = FMath::Lerp(m_fSpineDirection, fSpine, GetAnimInstance()->GetRotSpeed_Spine() * fDeltaTime);
		
		FRotator rResult_Head = FRotator(0.0f, m_fHeadDirection, 0.0f);
		m_pAnimInstance->SetStat_HeadRotator(rResult_Head);

		FRotator rResult_Spine = FRotator(0.0f, m_fSpineDirection, 0.0f);
		m_pAnimInstance->SetStat_SpineRotator(rResult_Spine);
	}
}

void AGBox::SlowGage_Tick(float fDeltaTime)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_SimpleMenu) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Landing) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_PortalJump) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_PortalFalling)) return;

	if (GetVisibleHUD() == false || m_bState_Pause == true || m_bSlowControl == false)
	{
		float fA = m_pHud->GetRootHUD()->GetSlowGageHUD()->GetDeActiveGageValue() / 100.0f * 1.0f;
		m_pHud->GetRootHUD()->GetSkillHUD()->Active_CoolTime(2, FMath::Abs(1.0f - fA));

		m_pHud->GetRootHUD()->GetSlowGageHUD()->DeActive_SlowGage();
		GetSlowMotion()->DeActive_SlowMotion();
		m_pPostProcessEffect->DeActive_Effect(TEXT("SlowMotion"));
		m_pGhostTrail->DeActive_TickGhostTrailEffect(TEXT("SlowMotion"));
		return;
	}

	if (m_pHud->GetRootHUD()->GetSlowGageHUD()->GetIsEmpty() == true)
	{
		float fA = m_pHud->GetRootHUD()->GetSlowGageHUD()->GetDeActiveGageValue() / 100.0f * 1.0f;
		m_pHud->GetRootHUD()->GetSkillHUD()->Active_CoolTime(2, FMath::Abs(1.0f - fA));

		m_pHud->GetRootHUD()->GetSlowGageHUD()->DeActive_SlowGage();
		GetSlowMotion()->DeActive_SlowMotion();
		m_pPostProcessEffect->DeActive_Effect(TEXT("SlowMotion"));
		m_pGhostTrail->DeActive_TickGhostTrailEffect(TEXT("SlowMotion"));
		return;
	}

	if (m_bSlowControl == false) return;

	if (GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftShift) == true)
	{
		m_pSoundMng->Play(TEXT("SlowStart"));
		SetSoundSlowMotion_On();
		
		GetSlowMotion()->Active_SlowMotion(1000.0f, 0.3f, 13.0f);
		m_pHud->GetRootHUD()->GetSlowGageHUD()->Active_SlowGage();
		m_pPostProcessEffect->Active_Effect(TEXT("SlowMotion"));
		m_pGhostTrail->Active_TickGhostTrailEffect(TEXT("SlowMotion"), 0.1f, 999.0f);		
	}
	
	if (GetKeyStateMng()->GetKeyIsJustRelease(EKeys::LeftShift) == true)
	{
		m_pSoundMng->Play(TEXT("SlowEnd"));
		SetSoundSlowMotion_Off();

		m_pHud->GetRootHUD()->GetSlowGageHUD()->DeActive_SlowGage();
		float fA = m_pHud->GetRootHUD()->GetSlowGageHUD()->GetDeActiveGageValue() / 100.0f * 1.0f;
		m_pHud->GetRootHUD()->GetSkillHUD()->Active_CoolTime(2, FMath::Abs(1.0f- fA));
		GetSlowMotion()->DeActive_SlowMotion();			
		m_pPostProcessEffect->DeActive_Effect(TEXT("SlowMotion"));
		m_pGhostTrail->DeActive_TickGhostTrailEffect(TEXT("SlowMotion"));
	}
}

void AGBox::DestroyShield()
{
	if (m_pShield != nullptr)
	{
		m_pShield->Destroy();
	}
	Delay_GodModOn();
}

void AGBox::PauseMenu_Tick()
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_SimpleMenu) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Landing) &&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_PortalJump)&&
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_PortalFalling)) return;
	
	if (m_bState_Dialoging == true)
	{
		return;
	}

	if (m_pPauseMenu->GetActive() == false && m_pPauseMenu->GetAniPlaying() == false)
	{
		if (GetKeyStateMng()->GetKeyIsJustPress(EKeys::Escape) == true ||
			GetKeyStateMng()->GetKeyIsJustPress(EKeys::Tab) == true && m_pPauseMenu->GetAniPlaying() == false)
		{
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Stage_3")
			{
				SetVisibleHUD(false);
				SetMovement(false);
				GetMouseMng()->SetMouseCamMove(false);
			}
			m_bState_Pause = true;
			m_pPauseMenu->Active_PauseMenu();
		}
	}
	else
	{

		if (GetKeyStateMng()->GetKeyIsJustPress(EKeys::Escape) == true ||
			GetKeyStateMng()->GetKeyIsJustPress(EKeys::Tab) == true && m_pPauseMenu->GetAniPlaying() == false)
		{
			m_bState_Pause = false;
			m_pPauseMenu->DeActive_PauseMenu();
		}

		if (m_pPauseMenu->Menu_GetButton() == 1)
		{
			m_pPauseMenu->DeActive_PauseMenu();
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Stage_3")
			{
				SetVisibleHUD(true);
				SetMovement(true);
				GetMouseMng()->SetMouseCamMove(true);
			}
			m_bState_Pause = false;
			//GetSlowMotion()->DeActive_SlowMotion();
			return;
		}
	}
	
}

float AGBox::GetNormalizeDir(float fAngle, float fRangeMin, float fRangeMax)
{
	//! 캐릭터가 바라보는 방향 360도를 -180 ~ 180 변환
	float fResult = UKismetMathLibrary::NormalizeAxis(fAngle);
	
	if (fResult <= fRangeMin)
	{
		fResult = fRangeMin;
	}
	else if (fResult >= fRangeMax)
	{
		fResult = fRangeMax;
	}

	return -fResult;
}

void AGBox::Shield_Tick(float fDeltaTime)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die))
	{
		return;
	}

	if (m_pShield != nullptr)
	{
		m_pShield->SetActorLocation(GetActorLocation());
	}

	if (m_bShield == true)
	{
		return;
	}

	m_fShieldTime_Curr += fDeltaTime;

	if (m_fShieldTime_Curr >= m_fShieldTime_End)
	{
		m_fShieldTime_Curr = 0.0f;
		
		if (m_pShield != nullptr)
		{
			m_pShield->Shield_Spawn();
		}
		m_bShield = true;
	}
	
}

void AGBox::SetPause(bool bPause)
{
	m_bState_Pause = bPause;
}

void AGBox::Delay_GodModOn()
{
	m_bDebug_GodMode = true;
	GetWorldTimerManager().SetTimer(m_pTimeDelay, this, &AGBox::Delay_GodModOff, 1.0f, false);
}

void AGBox::Delay_GodModOff()
{
	m_bDebug_GodMode = false;
	GetWorldTimerManager().ClearTimer(m_pTimeDelay);
}

float AGBox::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (m_bLife == false)
	{
		return 0.0f;
	}

	m_bState_Hit = true;

	GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	if (GetIsShield() == true)
	{
		SetShieldDestroy();

		return 0.000001f;
	}

	if (m_bDebug_GodMode == true)
	{
		return 0.0f;
	}

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fFinalDamage > 0.0f)
	{
		if (m_pStateMng->GetCurrentState() == (int)E_State_GBox::E_Attack)
		{
			UState_GBox_Attack* pState = Cast<UState_GBox_Attack>(m_pStateMng->GetStateClassRef((int)E_State_GBox::E_Attack));
			if (pState != nullptr)
			{
				bool bParring = pState->CheckParring(DamageCauser->GetActorLocation());
				if (bParring == true)
				{
					FDamageEvent* DamageEvent = new FDamageEvent_Parring(1.0f, GetActorLocation(), GetActorLocation());
					DamageCauser->TakeDamage(1.0f, *DamageEvent, GetController(), this);
					return 0.0f;
				}
			}
		}

		Tags.Empty();
		SetLife(false);
		SetVisibleHUD(false);
		m_fCurrentHp -= fFinalDamage;
		m_pShield->Shield_Destroy();
		m_pDieWidget->Active_Die(1.0f);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_Die));
	}

	return fFinalDamage;
}

void AGBox::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", m_pKeyStateMng, &UCpt_KeyStateMng::KB_Forward);
	PlayerInputComponent->BindAxis("MoveRight", m_pKeyStateMng, &UCpt_KeyStateMng::KB_Right);
}

void AGBox::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);
	
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->StateMessage(sMessage);
	}
}

void AGBox::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void AGBox::ControlMovement(FVector2D vKeyInput)
{
	FVector vKey3D = FVector(vKeyInput.X, vKeyInput.Y, 0.0f);
	FRotator rRota_Control = GetControlRotation();
	FRotator rRota_Control_Direction = FRotator(0.0f, rRota_Control.Yaw + 45.0f, 0.0f);
	FVector vContorl_ForwardVector = UKismetMathLibrary::GetForwardVector(rRota_Control_Direction);
	FVector vControl_RightVector = UKismetMathLibrary::GetRightVector(rRota_Control_Direction);

	AddMovementInput(vContorl_ForwardVector, vKeyInput.X);
	AddMovementInput(vControl_RightVector, vKeyInput.Y);
}

bool AGBox::Control_Attack(FVector vLoc)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die))
	{
		return false;
	}

	if (m_pHud->GetRootHUD()->GetSkillHUD()->GetCoolTimeState(0) == true)
	{
		return false;
	}

	if (m_bAttackControl == false) return false;

	UState_GBox_Attack* pState = Cast<UState_GBox_Attack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBox::E_Attack)));
	if (pState != nullptr)
	{
		m_pHud->GetRootHUD()->GetSkillHUD()->Active_CoolTime(0, 0.2f);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_Attack));

		return true;
	}

	return false;
}

bool AGBox::Control_Dodge()
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die))
	{
		return false;
	}

	if (m_pHud->GetRootHUD()->GetSkillHUD()->GetCoolTimeCountEmpty(1) == true)
	{
		return false;
	}

	if (m_bDashControl == false) return false;

	UState_GBox_Dodge* pState = Cast<UState_GBox_Dodge>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBox::E_Dodge)));
	if (pState != nullptr)
	{
		m_pHud->GetRootHUD()->GetSkillHUD()->Active_CoolTimeCount(1);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_Dodge));

		return true;
	}
	return false;
}

bool AGBox::Control_Portal(UArrowComponent* pStartPortal, UArrowComponent* pEndPortal)
{
	if (m_pStateMng == nullptr)
	{
		return false;
	}
	
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_Die))
	{
		return false;
	}

	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBox::E_PortalJump))
	{
		return false;
	}

	UState_GBox_PortalJump* pState = Cast<UState_GBox_PortalJump>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBox::E_PortalJump)));
	if (pState != nullptr)
	{
		SetVisibleHUD(false); 
		m_pStick->Control_Portal(true);		
		m_pStick->SetStickHidden(false);
		pState->SetPortalActor(pStartPortal, pEndPortal);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_PortalJump));

		return true;
	}

	return false;
}

void AGBox::SetAttackControl(bool bAttacking)
{
	m_bAttackControl = bAttacking;
}

void AGBox::SetDashControl(bool bDashing)
{
	m_bDashControl = bDashing;
}

void AGBox::SetSlowControl(bool bSlowing)
{
	m_bSlowControl = bSlowing;
}

void AGBox::SetMovement(bool bMovement)
{
	if (bMovement)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		EnableInput(PlayerController);
	}
	else
	{		
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		DisableInput(PlayerController);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
	}
	m_bMovement = bMovement;
}

void AGBox::SetVisibleHUD(bool bVisible)
{
	//ULOG(TEXT("HUD : %d"), bVisible);
	m_bVisibleHUD = bVisible;
}

void AGBox::SetVisibleDepth(int32 nValue)
{
	GetMesh()->CustomDepthStencilValue = nValue;
}

void AGBox::SetVisibleStick(bool bVisible)
{
	if (m_pStick != nullptr)
	{
		m_pStick->SetActorHiddenInGame(!bVisible);
	}
}

void AGBox::SetVisibleShield(bool bVisible)
{
	if (m_pShield != nullptr)
	{
		m_pShield->SetActorHiddenInGame(!bVisible);
	}
}

void AGBox::SetShieldDestroy()
{
	GetCamShake()->PlayCameraShake("AttackHit");
	GetPostProcessEffect()->Active_Effect("Hit");
	GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

	m_pSoundMng->Play("ShieldHit");
	m_pHud->GetRootHUD()->GetSkillHUD()->Active_ShieldCoolTime(m_fShieldTime_End);

	if (m_pShield != nullptr)
	{
		m_pShield->Shield_Destroy();
	}

	m_fShieldTime_Curr = 0.0f;

	SetShield(false);
}

void AGBox::CreateSpawn_Stick()
{
	if (m_pInstance_Stick == nullptr)
	{
		ULOG(TEXT("Stick Instance is Nullptr"));
		return;
	}

	FVector vPos = GetActorLocation();
	vPos.Z = 2000.0f;

	AStick* pSrc = GetWorld()->SpawnActor<AStick>(m_pInstance_Stick, vPos, FRotator::ZeroRotator);
	if (pSrc == nullptr)
	{
		return;
	}
	m_pStick = pSrc;
	pSrc->Spawn(this, GetActorLocation());	
}

AFootSmoke* AGBox::CreateFootSmoke()
{
	if (m_pInst_FootSmoke == nullptr)
	{
		return nullptr;
	}

	AFootSmoke* pFOotSmoke = GetWorld()->SpawnActor<AFootSmoke>(m_pInst_FootSmoke);
	if (pFOotSmoke == nullptr)
	{
		return nullptr;
	}

	return pFOotSmoke;
}

class AShield* AGBox::CreateShield()
{
	if (m_pInst_Shield == nullptr)
	{
		return nullptr;
	}

	AShield* pSrc = GetWorld()->SpawnActor<AShield>(m_pInst_Shield);
	if (pSrc == nullptr)
	{
		return nullptr;
	}
	pSrc->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, TEXT("Bip001"));
	pSrc->Shield_Destroy();

	return pSrc;
}

void AGBox::SetStick_MouseRot(bool bRot)
{
	if (m_pStick == nullptr)
	{
		return;
	}

	m_pStick->SetMouseRotation(bRot);
}

void AGBox::ShowResult()
{
	if (m_pResultWidget == nullptr)
	{
		return;
	}

	TArray<FString> sResultList;
	sResultList.Add(FString::FromInt(m_pSaveMng->Load_Data()->m_stPlayerData.m_nHitBulletCount));
	sResultList.Add(FString::FromInt(m_pSaveMng->Load_Data()->m_stPlayerData.m_nNonHitBulletCount));
	sResultList.Add(FString::FromInt(m_pSaveMng->Load_Data()->m_stPlayerData.m_nDeadCount));

	m_pResultWidget->SetDataInit(sResultList);

	SetVisibleHUD(false);
	m_pResultWidget->Active_HUD();

	sResultList.Empty();
}