// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_SlowGage.generated.h"

UENUM()
enum class E_State_SlowGage : uint8
{
	E_SLOW_NONE,
	E_SLOW_ACTIVE,
	E_SLOW_DEACTIVE,

	E_MAX,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UCpt_SlowGage : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_SlowTimeGage> m_pInst_Widget;

	UPROPERTY()
		class UWidget_SlowTimeGage* m_pWidget;

	UPROPERTY()
		class AActor* m_pRootChar;

	int32 m_eState;

	float m_fGageValue = 0.0f;
	const float m_fGageSpeed = 1.0f;
	
	bool m_bIsFullGage = false;
	
public:
	UCpt_SlowGage();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetInit(class AActor* pActor, FVector2D vPos = FVector2D::ZeroVector);
	void SetDestroy();
	void SlowTargetTick(AActor* pTarget);

	void Active_Slow();
	void DeActive_Slow();

public:
	FORCEINLINE bool GetIsFullGage() { return m_bIsFullGage;  }
};
