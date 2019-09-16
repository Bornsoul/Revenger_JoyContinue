// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "MovePortal.generated.h"

UCLASS()
class REVENGER_API AMovePortal : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		TArray<class UCpt_PortalArrow*> m_pPortalArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PortalMesh, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_pCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PortalMesh, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* m_pColliderPortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PortalMesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_pPortal;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	UPROPERTY()
		class AGBox* m_pPlayer;

	UPROPERTY()
		class UCpt_PortalArrow* m_pStartPortal;

	UPROPERTY()
		class UCpt_PortalArrow* m_pEndPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		bool m_bPortalActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		int32 m_nCurPortal = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		int32 m_nNextPortal = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		bool m_bUseAndDestroy = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		float m_fDestroyTime = 1.0f;
	
	FVector m_vColliderSize = FVector::ZeroVector;

	bool m_bActive = false;
	bool m_bGetIn = false;

	float m_fDestroyTime_Cur = 0.0f;
	float m_fDestroyTime_End = 2.0f;
	bool m_bDestroy = false;
	bool m_bUsed = false;

	bool m_bJHActive = false;

public:	
	AMovePortal();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void SpawnPortal();
	UFUNCTION(BlueprintPure)
		bool GetActive() { return m_bActive; }

	UFUNCTION(BlueprintCallable)
	void SetCircleActive(bool bActive);
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



public:

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetPortalActive() { return m_bPortalActive; }

	FORCEINLINE int32 GetCurPortal() { return m_nCurPortal; }
	FORCEINLINE int32 GetNextPortal() { return m_nNextPortal; }
	//FORCEINLINE class UCpt_PortalArrow* GetPortalArrow() { return m_pPortalArrow; }
	FORCEINLINE class UCpt_KeyStateMng* GetKeyStateMng() { return m_pKeyStateMng; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetUsed() { return m_bUsed; }
};
