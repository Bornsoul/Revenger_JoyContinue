// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraShake.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_CamShake.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_CamShake : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, TSubclassOf<UCameraShake>> m_pCSList;

	UPROPERTY()
		class APlayerCameraManager* m_pCameraManager;

public:
	UCpt_CamShake();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! UCameraShake Blueprint ���� ���
	//! FString sName : ����� �̸�
	//! FString sPath : Blueprint ���� ���
	void AddCameraShakeClass(FString sName, FString sPath);

	//! CamShake ���
	//! FString sCamShakeName					 : ����� ķ����ũ �̸�
	//! float fScale							 : ����� ������(�������� ũ�� ������ ���ÿ��� �� ȿ���� Ŀ��)
	//! ECameraAnimPlaySpace::Type pAnimSpace	 : ����� ��ǥ Space ����
	void PlayCameraShake(FString sCamShakeName, float fScale = 1.0f, ECameraAnimPlaySpace::Type pAnimSpace = ECameraAnimPlaySpace::CameraLocal);

	//! ��ϵ� CamShake Blueprint���� ã��
	TSubclassOf<UCameraShake> GetCameraShakeClass(FString sName);
};