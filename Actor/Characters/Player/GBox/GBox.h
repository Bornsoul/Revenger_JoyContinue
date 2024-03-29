// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Libraries/Components/MouseMng/Cpt_MouseMng.h"

#include "Revenger.h"
#include "Actor/Characters/Player/GC_Player.h"
#include "GBox.generated.h"

UCLASS()
class REVENGER_API AGBox : public AGC_Player, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_pCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_pSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* m_pArrowComp;

	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_GBox* m_pAnimInstance;

	UPROPERTY()
		class UStateMng_GBox* m_pStateMng;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	UPROPERTY()
		class UCpt_SlowMotion* m_pSlowMotion;

	UPROPERTY()
		class UCpt_CamShake* m_pCamShake;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "PostProcess")
		class UPostProcessComponent* m_pPostProcess;

	UPROPERTY()
		class UCpt_PostProcessEffect* m_pPostProcessEffect;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MouseLand, meta = (AllowPrivateAccess = "true"))
		class UCpt_MouseLandMng* m_pMouseLandMng;

	UPROPERTY()
		class AHUD_Game* m_pHud;

	UPROPERTY()
		class UCpt_GhostTrail* m_pGhostTrail;

	UPROPERTY()
		class UCpt_FootPushLine* m_pFootPushLine;

	UPROPERTY(EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
		class TSubclassOf<class AStick> m_pInstance_Stick;

	UPROPERTY()
		class AStick* m_pStick;
	
	UPROPERTY()
		class UCpt_ResultWidget* m_pResultWidget;

	UPROPERTY()
		class UCpt_DieScreen* m_pDieWidget;

	UPROPERTY()
		class TSubclassOf<class AFootSmoke> m_pInst_FootSmoke;

	UPROPERTY()
		class TSubclassOf<class AShield> m_pInst_Shield;

	UPROPERTY()
		class UCpt_SimpleMenu* m_pSimpleMenu;

	UPROPERTY()
		class UCpt_PauseMenu* m_pPauseMenu;

	UPROPERTY()
		class AShield* m_pShield;

	UPROPERTY()
		class UCpt_GameSave* m_pSaveMng;


	bool m_bMovement = false;
	bool m_bVisibleHUD = false;
	bool m_bAttackControl = false;
	bool m_bDashControl = false;
	bool m_bSlowControl = false;
	
	float m_fGlobalTime = 1.0f;
	FTimerHandle m_pTimeDelay;

	bool m_bShield = true;
	float m_fShieldTime_Curr = 0.0f;
	float m_fShieldTime_End = 0.0f;

	float m_fHeadDirection = 0.0f;
	float m_fSpineDirection = 0.0f;

	int32 m_nSpawnPoint = -1;	
	int32 m_nDeadCount = 0;
	int32 m_nDifficultLevel = -1;

	bool m_bState_Hit = false;
	bool m_bState_Pause = false;
	bool m_bDebug_GodMode = false;
	bool m_bState_Dialoging = false;
	
public:
	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 10.0f;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fShield_ReCharge_Time = 5.0f;

	UPROPERTY(EditAnywhere, Category = UIOption)
		FVector2D m_vSlowGagePos;

public :
	FORCEINLINE class UCpt_PauseMenu* GetPauseMenu() { return m_pPauseMenu; }

	FORCEINLINE class UCameraComponent* GetCamera() { return m_pCamera; }
	FORCEINLINE class UAnimInst_GBox* GetAnimInstance() { return m_pAnimInstance; }
	FORCEINLINE class UCpt_KeyStateMng* GetKeyStateMng() { return m_pKeyStateMng; }	
	FORCEINLINE class UCpt_CamShake* GetCamShake() { return m_pCamShake; }
	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
	FORCEINLINE class UCpt_PostProcessEffect* GetPostProcessEffect() { return m_pPostProcessEffect; }
	FORCEINLINE class UCpt_SlowMotion* GetSlowMotion() { return m_pSlowMotion; }
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_SoundMng* GetSoundMng() { return m_pSoundMng; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() { return m_pSpringArm; }
	FORCEINLINE class UCpt_GhostTrail* GetGhostTrail() { return m_pGhostTrail; }
	
	FORCEINLINE class AFootSmoke* CreateFootSmoke();

	FORCEINLINE class AShield* CreateShield();

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class AStick* GetStick() { return m_pStick; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class AShield* GetShield() { return m_pShield; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class AHUD_Game* GetHUD() { return m_pHud; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCpt_MouseLandMng* GetMouseMng() { return m_pMouseLandMng; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCpt_GameSave* GetGameSaveMng() { return m_pSaveMng; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UStateMng_GBox* GetStateMng() { return m_pStateMng; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCpt_SimpleMenu* GetSimpleMenu() { return m_pSimpleMenu; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetMovement() { return m_bMovement; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetVisibleHUD() { return m_bVisibleHUD; }
	   
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetAttackControl() { return m_bAttackControl; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetDashControl() { return m_bDashControl; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetSlowControl() { return m_bSlowControl; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetIsShield() { return m_bShield; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetIsHit() { return m_bState_Hit; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetIsDialoging() { return m_bState_Dialoging; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetDebug_GodMod() { return m_bDebug_GodMode;  }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetDifficultLevel() { return m_nDifficultLevel; }

public:
	AGBox();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AnimInst_Tick(float fDeltaTime);
	void PauseMenu_Tick();
	void SlowGage_Tick(float fDeltaTime);
	void Shield_Tick(float fDeltaTime);
	
	void SetPause(bool bPause);

	void Delay_GodModOn();
	void Delay_GodModOff();

	void ControlMovement(FVector2D vKeyInput);
	bool Control_Attack(FVector vLoc);
	bool Control_Dodge();
	
	void SetHitState(bool bHit) { m_bState_Hit = bHit; }

	void CreateSpawn_Stick();
	void SetStick_MouseRot(bool bRot);
	
	void DestroyShield();
	
	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetDialoging(bool bDialoging) { m_bState_Dialoging = bDialoging; }

	UFUNCTION(BlueprintCallable)
		void ShowResult();

	UFUNCTION(BlueprintCallable)
		bool Control_Portal(UArrowComponent* pStartPortal, UArrowComponent* pEndPortal);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetAttackControl(bool bAttacking);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetDashControl(bool bDashing);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetSlowControl(bool bSlowing);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetMovement(bool bMovement);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetVisibleHUD(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetVisibleDepth(int32 nValue);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetVisibleStick(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetShield(bool bShield) { m_bShield = bShield; }

	UFUNCTION(BlueprintCallable, Category="GBox Visible")
		void SetVisibleShield(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetDebug_GodMod(bool bGod) { m_bDebug_GodMode = bGod; }

	UFUNCTION(BlueprintCallable, Category = "GBox Visible")
		void SetShieldDestroy();

private:
	float GetNormalizeDir(float fAngle, float fRangeMin, float fRangeMax);

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void SetSoundSlowMotion_On();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void SetSoundSlowMotion_Off();
};
