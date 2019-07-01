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
		TMap<FString, class UAudioComponent*> m_pAudio;		//! �� ���帶�� UAudioComponent1���� ������ �װ� �����ϴ� TMap

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, USoundCue*> m_pSoundList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, USoundAttenuation*> m_pAttenuationList;

	//! SoundList Ŭ������ USoundCue �����͸���Ʈ
	UPROPERTY()
		TMap<FString, USoundCue*> m_pSoundList_FromList;
	//! SoundList Ŭ������ USoundAttenuation �����͸���Ʈ
	UPROPERTY()
		TMap<FString, USoundAttenuation*> m_pAttenuationList_FromList;
public:
	UCpt_SoundMng();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//void AddSoundList(class TSubclassOf<class USoundList> pList);

	//! USoundList Blueprint ���� ����Ʈ ����
	//! FString sPath : Blueprint ���
	void Set_SoundList(FString sPath);

	//! ���� ���
	void Play(FString sCueName);

	//! ���� ���_��ü����
	//! FString sCueName : List�� ��ϵ� ���� �̸�
	//! FString sAttenuationName : List�� ��ϵ� Attenuation �̸�
	//! FVector pLocation : ���� �߻� ��ǥ
	void Play_Spatialization(FString sCueName, FString sAttenuationName, FVector pLocation);

	//! ���� ����
	void Stop(FString sCueName);

	//! ���� ���� ����
	//! FString sCueName : List�� ��ϵ� ���� �̸�
	//! float fValue : ������ (1.0f�� �⺻��)
	void SetVolume(FString sCueName, float fValue);

	//! UAudioComponent ����Ʈ���� �̸��� ã�Ƽ� ��ȯ
	class UAudioComponent* GetAudioComponent(FString sCueName);


	//! ���� ����Ʈ Ž�� ��ȯ
	USoundCue* GetSoundCueAsString(FString sCueName);
	USoundAttenuation* GetAttenuation(FString sName);

};