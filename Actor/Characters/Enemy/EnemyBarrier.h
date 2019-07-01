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
		int m_nHp = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
		bool m_bActive = false;
public:	
	AEnemyBarrier();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Init(int nHp = 5)
	{
		m_nHp = nHp;
	}

	bool GetActiveState() { return m_bActive; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Active_Barrier();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Hit_Barrier(int nDamage = 1);
};
