// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/HUD.h"
#include "HUD_Game.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AHUD_Game : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = Option)
		TSubclassOf<class UWidget_GHUD> m_pInst_MainHUD;

	UPROPERTY()
		class UWidget_GHUD* m_pMainHUD;

	UPROPERTY()
		class UCpt_OSIMng* m_pOSIMng;

	UPROPERTY()
		class APlayerController* m_pController;

	bool m_bActive = false;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fGageSpeed = 50.0f;

	bool m_bDestroyOSI = false;
public:
	AHUD_Game();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Init();

	void SetHudActive(bool bActive);

public:

	UFUNCTION(BlueprintPure)
		class UWidget_GHUD* GetRootHUD();// { return m_pMainHUD; }

	void AddOSIEnemy(class AGameCharacter* pEnemy, int32 nIconState);
	void DestroyOSIEnemy();

	FORCEINLINE class UCpt_OSIMng* GetOSIMng() { return m_pOSIMng; }
	FORCEINLINE bool GetHudActive() { return m_bActive; }

};