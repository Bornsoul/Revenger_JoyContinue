#include "Cpt_SlowMotion.h"
#include "Kismet/KismetMathLibrary.h"

UCpt_SlowMotion::UCpt_SlowMotion()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_SlowMotion::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCpt_SlowMotion::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Tick_SlowMotion(DeltaTime);
	// ...
}

void UCpt_SlowMotion::Active_SlowMotion(float fActiveTime, float fSlowPower, float fChangeSpeed)
{
	m_bActive = true;
	m_fSlowActiveTime = fActiveTime;
	m_fSlowPower = fSlowPower;
	m_fChangeSpeed = fChangeSpeed;
	m_fSlow_CurrentValue = UGameplayStatics::GetGlobalTimeDilation(GetOwner()->GetWorld());
	m_nStateCnt = 0;

	m_fRealTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void UCpt_SlowMotion::Tick_SlowMotion(float fDeltatime)
{
	if (m_bActive != true) return;

	switch (m_nStateCnt)
	{
	case 0:
		Tick_Enter(fDeltatime);
		break;
	case 1:
		Tick_Process(fDeltatime);
		break;
	case 2:
		Tick_End(fDeltatime);
		break;
	}
}

void UCpt_SlowMotion::DeActive_SlowMotion()
{
	m_nStateCnt = 2;
}

void UCpt_SlowMotion::Tick_Enter(float fDeltaTime)
{
	m_fSlow_CurrentValue = UKismetMathLibrary::FInterpTo(m_fSlow_CurrentValue, m_fSlowPower, fDeltaTime, m_fChangeSpeed);
	UGameplayStatics::SetGlobalTimeDilation(GetOwner()->GetWorld(), m_fSlow_CurrentValue);

	if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fRealTime >= m_fSlowActiveTime)
	{
		DeActive_SlowMotion();
	}

}

void UCpt_SlowMotion::Tick_Process(float fDeltaTime)
{

}

void UCpt_SlowMotion::Tick_End(float fDeltaTime)
{
	bool bEnd = false;
	if (m_fSlow_CurrentValue >= 0.95f)
	{
		m_fSlow_CurrentValue = 1.0f;
		bEnd = true;
	}
	m_fSlow_CurrentValue = UKismetMathLibrary::FInterpTo(m_fSlow_CurrentValue, 1.0f, fDeltaTime, m_fChangeSpeed);
	UGameplayStatics::SetGlobalTimeDilation(GetOwner()->GetWorld(), m_fSlow_CurrentValue);

	if (bEnd == true)
	{
		m_bActive = false;
	}
}