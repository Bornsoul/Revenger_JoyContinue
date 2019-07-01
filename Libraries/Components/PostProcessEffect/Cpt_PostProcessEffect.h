// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_PostProcessEffect.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_PostProcessEffect : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UPostProcessComponent* m_pPostProcess;

protected:
	UPROPERTY()
		TMap<FString, TSubclassOf<class UPostProcessEffect_Root>> m_pPostprocessEffect_List;	//! PPE List(PostProcessEffect)

	UPROPERTY()
		TMap<FString, class UPostProcessEffect_Root*> m_pPostprocessEffect_SpawnList;

	bool m_bInit = false;

public:
	UCpt_PostProcessEffect();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! 부모 Actor에서 PostProcessCompoent 받기
	void Init(class UPostProcessComponent* pPostProcess);

	//! PostProcessEffect 추가
	//! FString sName : 활용할 이름
	//! FString sPath : UPostProcessEffect_Root Blueprint 경로
	void Add_PostProcessEffect(FString sName, FString sPath);

	//! PostProcessEffect 활성화, TMap리스트에서 해당 이펙트를 찾아서 활성화 시킨다.
	//! FString sName : Add_PostProcessEffect에서 추가 할때 사용한 sName을 입력
	void Active_Effect(FString sName);

	//! PostProcessEffect 비활성화, sName의 PPE를 찾아서 비활성화 시킨다.
	//! FString sName : Add_PostProcessEffect에서 추가 할때 사용한 sName을 입력
	void DeActive_Effect(FString sName);

	//! 모든 이펙트 비활성화
	void DeActive_AllEffect();
};
