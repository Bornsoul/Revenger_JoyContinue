#include "Cpt_SoundMng.h"
#include "Res_SoundList.h"

UCpt_SoundMng::UCpt_SoundMng()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCpt_SoundMng::BeginPlay()
{
	Super::BeginPlay();

	for (TMap<FString, USoundCue*>::TIterator it = m_pSoundList.CreateIterator(); it; ++it)
	{
		UAudioComponent* pAuCom = NewObject<UAudioComponent>(this);
		pAuCom->bAutoActivate = false;
		pAuCom->bAutoManageAttachment = true;
		pAuCom->SetSound(Cast<USoundBase>(it->Value));
		m_pAudio.Add(it->Key, pAuCom);
	}

	for (TMap<FString, USoundCue*>::TIterator it = m_pSoundList_FromList.CreateIterator(); it; ++it)
	{
		UAudioComponent* pAudio = GetAudioComponent(it->Value->GetName());
		if (pAudio != nullptr) continue;

		UAudioComponent* pAuCom = NewObject<UAudioComponent>(this);
		pAuCom->bAutoActivate = false;
		pAuCom->SetSound(Cast<USoundBase>(it->Value));
		m_pAudio.Add(it->Key, pAuCom);
	}
}

void UCpt_SoundMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCpt_SoundMng::Set_SoundList(FString sPath)
{
	FText TextVariable = FText::AsCultureInvariant(sPath);
	ConstructorHelpers::FClassFinder<URes_SoundList> Const_SoundList(*sPath);
	if (Const_SoundList.Succeeded())
	{
		URes_SoundList* pSoundList = Const_SoundList.Class->GetDefaultObject<URes_SoundList>();

		m_pSoundList_FromList = pSoundList->GetSoundList();
		m_pAttenuationList_FromList = pSoundList->GetAttenuationList();
	}
}

void UCpt_SoundMng::Play(FString sCueName)
{
	UAudioComponent* pAudio = GetAudioComponent(sCueName);
	if (pAudio != nullptr) pAudio->Play();

}

void UCpt_SoundMng::Play_Spatialization(FString sCueName, FString sAttenuationName, FVector pLocation)
{
	UAudioComponent* pAudio = GetAudioComponent(sCueName);
	USoundAttenuation* pAttenuation = GetAttenuation(sAttenuationName);
	if (pAudio == nullptr) return;

	pAudio->SetWorldLocation(pLocation);
	pAudio->bAllowSpatialization = true;
	pAudio->bIsUISound = false;
	pAudio->AttenuationSettings = pAttenuation;
	if (pAudio != nullptr) pAudio->Play();
}

void UCpt_SoundMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (TMap<FString, UAudioComponent*>::TIterator it = m_pAudio.CreateIterator(); it; ++it)
	{
		it->Value->DestroyComponent();
		it->Value = nullptr;
	}
	m_pAudio.Empty();
}

void UCpt_SoundMng::Stop(FString sCueName)
{
	UAudioComponent* pAudio = GetAudioComponent(sCueName);
	if (pAudio != nullptr) pAudio->Stop();
}

void UCpt_SoundMng::SetVolume(FString sCueName, float fValue)
{
	UAudioComponent* pAudio = GetAudioComponent(sCueName);
	if (pAudio != nullptr) pAudio->SetVolumeMultiplier(fValue);
}

UAudioComponent * UCpt_SoundMng::GetAudioComponent(FString sCueName)
{
	for (TMap<FString, UAudioComponent*>::TIterator it = m_pAudio.CreateIterator(); it; ++it)
	{
		if (it->Key != sCueName)
		{
			continue;
		}
		return it->Value;
	}
	return nullptr;
}

USoundCue * UCpt_SoundMng::GetSoundCueAsString(FString sCueName)
{
	for (TMap<FString, USoundCue*>::TIterator it = m_pSoundList.CreateIterator(); it; ++it)
	{
		if (it->Value->GetName() == sCueName)
		{
			return it->Value;
		}
	}

	for (TMap<FString, USoundCue*>::TIterator it = m_pSoundList_FromList.CreateIterator(); it; ++it)
	{
		if (it->Value->GetName() == sCueName)
		{
			return it->Value;
		}
	}

	return nullptr;
}

USoundAttenuation * UCpt_SoundMng::GetAttenuation(FString sName)
{
	for (TMap<FString, USoundAttenuation*>::TIterator it = m_pAttenuationList.CreateIterator(); it; ++it)
	{
		if (it->Value->GetName() == sName)
		{
			return it->Value;
		}
	}

	for (TMap<FString, USoundAttenuation*>::TIterator it = m_pAttenuationList_FromList.CreateIterator(); it; ++it)
	{
		if (it->Value->GetName() == sName)
		{
			return it->Value;
		}
	}
	return nullptr;
}

