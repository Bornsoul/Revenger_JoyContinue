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

	//! �θ� Actor���� PostProcessCompoent �ޱ�
	void Init(class UPostProcessComponent* pPostProcess);

	//! PostProcessEffect �߰�
	//! FString sName : Ȱ���� �̸�
	//! FString sPath : UPostProcessEffect_Root Blueprint ���
	void Add_PostProcessEffect(FString sName, FString sPath);

	//! PostProcessEffect Ȱ��ȭ, TMap����Ʈ���� �ش� ����Ʈ�� ã�Ƽ� Ȱ��ȭ ��Ų��.
	//! FString sName : Add_PostProcessEffect���� �߰� �Ҷ� ����� sName�� �Է�
	void Active_Effect(FString sName);

	//! PostProcessEffect ��Ȱ��ȭ, sName�� PPE�� ã�Ƽ� ��Ȱ��ȭ ��Ų��.
	//! FString sName : Add_PostProcessEffect���� �߰� �Ҷ� ����� sName�� �Է�
	void DeActive_Effect(FString sName);

	//! ��� ����Ʈ ��Ȱ��ȭ
	void DeActive_AllEffect();
};
