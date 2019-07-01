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

	//! UCameraShake Blueprint 파일 등록
	//! FString sName : 등록할 이름
	//! FString sPath : Blueprint 파일 경로
	void AddCameraShakeClass(FString sName, FString sPath);

	//! CamShake 재생
	//! FString sCamShakeName					 : 등록한 캠쉐이크 이름
	//! float fScale							 : 재생할 스케일(스케일이 크면 지정된 세팅에서 더 효과가 커짐)
	//! ECameraAnimPlaySpace::Type pAnimSpace	 : 재생할 좌표 Space 설정
	void PlayCameraShake(FString sCamShakeName, float fScale = 1.0f, ECameraAnimPlaySpace::Type pAnimSpace = ECameraAnimPlaySpace::CameraLocal);

	//! 등록된 CamShake Blueprint파일 찾기
	TSubclassOf<UCameraShake> GetCameraShakeClass(FString sName);
};