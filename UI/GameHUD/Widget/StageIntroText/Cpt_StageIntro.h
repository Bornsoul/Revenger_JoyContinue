// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_StageIntro.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_StageIntro : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_StageIntro> m_pInst_Widget;

	UPROPERTY()
		class UWidget_StageIntro* m_pWidget;

	float m_fStartDelay_Curr = 0.0f;
	float m_fStartDelay_End = 0.0f;
	bool m_bStartDelay = false;

	float m_fEndTime_Curr = 0.0f;
	float m_fEndTime_End = 0.0f;

	bool m_bPlaying = false;

public:	
	// Sets default values for this component's properties
	UCpt_StageIntro();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	void SetInit();
	void SetPlay(float fStartDelay = 0.0f, float fEndTime = 2.0f);
	void SetEndPlay();

private:
	void SetPosition(FVector vPos);

public:
	FORCEINLINE bool GetIsPlaying() { return m_bPlaying; }
};
