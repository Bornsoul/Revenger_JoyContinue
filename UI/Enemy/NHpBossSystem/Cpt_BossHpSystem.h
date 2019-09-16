// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_BossHpSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_BossHpSystem : public UActorComponent
{
	GENERATED_BODY()
		
private:

	UPROPERTY()
		TSubclassOf<class UWidget_BossHpHUD> m_pInst_HUD;

	UPROPERTY()
		TSubclassOf<class UWidget_BossHpItem> m_pInst_Item;
	
	UPROPERTY()
		TSubclassOf<class UWidget_BossShieldItem> m_pInst_Shield;

	UPROPERTY()
		TSubclassOf<class UWidget_EnemyBossTitle> m_pInst_TitleWidget;


	UPROPERTY()
		class UWidget_BossHpHUD* m_pHud;

	UPROPERTY()
		TArray<class UWidget_BossHpItem*> m_pHpItemList;

	UPROPERTY()
		TArray<class UWidget_BossShieldItem*> m_pShieldItemList;

	UPROPERTY()
		class UWidget_EnemyBossTitle* m_pTitleWidget;
	

	UPROPERTY()
		APlayerController* m_pController;

	FTimerHandle m_pDestroyTime;

public:	
	UCpt_BossHpSystem();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void CreateHpShield(float fHp, float fShield);

	UFUNCTION(BlueprintCallable)
		void Hit_Hp(const bool bAll = false);

	UFUNCTION(BlueprintCallable)
		void Hit_Shield(const bool bAll = false);

	UFUNCTION(BlueprintCallable)
		void Heal_Hp(const bool bAll = false);
	
	UFUNCTION(BlueprintCallable)
		void Heal_Shield(const bool bAll = false);

	UFUNCTION(BlueprintCallable)
		void Animation_Hp(const FString sAniName, const bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void Animation_Shield(const FString sAniName, const bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void DestroySystem();

	void DestroySelf();

	class UWidget_BossHpItem* Add_HpItem();
	class UWidget_BossShieldItem* Add_ShieldItem();
	class UWidget_EnemyBossTitle* Add_TitleItem();

};
