// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_SoundMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_SoundMng : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TMap<FString, class UAudioComponent*> m_pAudio;		//! 각 사운드마다 UAudioComponent1개씩 생성됨 그걸 관리하는 TMap

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, USoundCue*> m_pSoundList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, USoundAttenuation*> m_pAttenuationList;

	//! SoundList 클래스의 USoundCue 포인터리스트
	UPROPERTY()
		TMap<FString, USoundCue*> m_pSoundList_FromList;
	//! SoundList 클래스의 USoundAttenuation 포인터리스트
	UPROPERTY()
		TMap<FString, USoundAttenuation*> m_pAttenuationList_FromList;
public:
	UCpt_SoundMng();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//void AddSoundList(class TSubclassOf<class USoundList> pList);

	//! USoundList Blueprint 사운드 리스트 세팅
	//! FString sPath : Blueprint 경로
	void Set_SoundList(FString sPath);

	//! 사운드 재생
	void Play(FString sCueName);

	//! 사운드 재생_입체사운드
	//! FString sCueName : List에 등록된 사운드 이름
	//! FString sAttenuationName : List에 등록된 Attenuation 이름
	//! FVector pLocation : 사운드 발생 좌표
	void Play_Spatialization(FString sCueName, FString sAttenuationName, FVector pLocation);

	//! 사운드 정지
	void Stop(FString sCueName);

	//! 사운드 볼륨 설정
	//! FString sCueName : List에 등록된 사운드 이름
	//! float fValue : 볼륨값 (1.0f이 기본값)
	void SetVolume(FString sCueName, float fValue);

	//! UAudioComponent 리스트에서 이름을 찾아서 반환
	class UAudioComponent* GetAudioComponent(FString sCueName);


	//! 사운드 리스트 탐색 반환
	USoundCue* GetSoundCueAsString(FString sCueName);
	USoundAttenuation* GetAttenuation(FString sName);

};