// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/HUD.h"
#include "HUD_GameMain.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AHUD_GameMain : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category=Option)
		TSubclassOf<class UWidget_GameHUD> m_pInst_MainHUD;

	UPROPERTY()
		class UWidget_GameHUD* m_pMainHUD;

	UPROPERTY()
		class UCpt_OSIMng* m_pOSIMng;

public:
	AHUD_GameMain();
	virtual void BeginPlay() override;
	void Init();
	void AddViewPort();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	class UWidget_GameHUD* GetRootHUD() { return m_pMainHUD; }
	void AddOSIEnemy(class AGameCharacter* pEnemy);

	FORCEINLINE class UCpt_OSIMng* GetOSIMng() { return m_pOSIMng; }
};
