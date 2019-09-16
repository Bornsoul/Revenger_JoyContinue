// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBarrier.generated.h"

UCLASS()
class REVENGER_API AEnemyBarrier : public AActor
{
	GENERATED_BODY()
	
private :	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
		int32 m_nHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
		int32 m_nMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
		bool m_bActive = false;
public:	
	AEnemyBarrier();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Init(int nHp)
	{
		m_nHp = nHp;
		m_nMaxHp = nHp;
	}
	
	UFUNCTION(BlueprintCallable)
		void SetCurrentHp(int32 nCurHp) { m_nHp= nCurHp; }

	UFUNCTION(BlueprintCallable)
		void SetMaxHp(int32 nMaxHp) { m_nMaxHp = nMaxHp; }

	UFUNCTION(BlueprintPure)
		bool GetActiveState() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		int32 GetCurHp() { return m_nHp; }

	UFUNCTION(BlueprintPure)
		int32 GetMaxHp() { return m_nMaxHp; }


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Active_Barrier();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Hit_Barrier(int nDamage = 1);
};
