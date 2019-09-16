// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "Act_SpawnPoint.generated.h"

UCLASS()
class REVENGER_API AAct_SpawnPoint : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		int32 m_nCurrentPoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		float m_fSaveAlertTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		bool m_bDebuging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_pBoxColider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* m_pSpawnArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnOption", Meta = (AllowPrivateAccess = "true"))
		class UCpt_GameSave* m_pComp_Save;


	bool m_bInRound = false;

public:	
	AAct_SpawnPoint();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void SetInRound(bool bRound) { m_bInRound = bRound; }

	UFUNCTION(BlueprintPure)
		bool GetInRound() { return m_bInRound; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentPoint(int32 nPoint) { m_nCurrentPoint = nPoint;  }

	UFUNCTION(BlueprintPure)
		int32 GetCurrentPoint() { return m_nCurrentPoint; }

	UFUNCTION(BlueprintPure)
		class UArrowComponent* GetSpawnArrow() { return m_pSpawnArrow; }
};
