#include "Cpt_KeyStateMng.h"
#include "KIsmet/GameplayStatics.h"
#include "Engine/World.h"

UCpt_KeyStateMng::UCpt_KeyStateMng()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_KeyStateMng::BeginPlay()
{
	Super::BeginPlay();

	m_vKeyInput = FVector2D::ZeroVector;
	m_pOwner = GetOwner();

	/*AddKeyState("Attack");
	AddKeyState("Dash");
	AddKeyState("TraceDash");
	AddKeyState("ComboAtk");*/
}

void UCpt_KeyStateMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pKeyStates.Empty();
}

void UCpt_KeyStateMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (TMap<FString, ST_KeyStateMng>::TIterator it = m_pKeyStates.CreateIterator(); it; ++it)
	{
		if (it->Value.bKeyState == false) continue;
		it->Value.fPressTime += DeltaTime;
	}
}

bool UCpt_KeyStateMng::GetAnyKeyIsDown()
{
	if (m_vKeyInput == FVector2D::ZeroVector) return false;
	return true;
}

bool UCpt_KeyStateMng::GetKeyIsDown(const FKey Key)
{
	if (m_pOwner == nullptr) return false;
	if (UGameplayStatics::GetPlayerController(m_pOwner->GetWorld(), 0)->IsInputKeyDown(Key) == true)
	{
		return true;
	}
	return false;
}

bool UCpt_KeyStateMng::GetKeyIsJustPress(const FKey Key)
{
	if (m_pOwner == nullptr) return false;
	if (UGameplayStatics::GetPlayerController(m_pOwner->GetWorld(), 0)->WasInputKeyJustPressed(Key) == true)
	{
		return true;
	}
	return false;
}

bool UCpt_KeyStateMng::GetKeyIsJustRelease(const FKey Key)
{
	if (m_pOwner == nullptr) return false;
	if (UGameplayStatics::GetPlayerController(m_pOwner->GetWorld(), 0)->WasInputKeyJustReleased(Key) == true)
	{
		return true;
	}
	return false;
}

void UCpt_KeyStateMng::AddKeyState(FString sStr)
{
	ST_KeyStateMng pState;
	pState.bKeyState = false;
	pState.fPressTime = 0.0f;

	m_pKeyStates.Add(sStr, pState);
}

void UCpt_KeyStateMng::KB_Forward(float fValue)
{
	m_vKeyInput.X = fValue;
}

void UCpt_KeyStateMng::KB_Right(float fValue)
{
	m_vKeyInput.Y = fValue;
}

void UCpt_KeyStateMng::KB_Attack_Down()
{
	if (m_pKeyStates["Attack"].bKeyState == false)
	{
		m_pKeyStates["Attack"].fPressTime = 0.0f;
	}
	m_pKeyStates["Attack"].bKeyState = true;
}

void UCpt_KeyStateMng::KB_Attack_Up()
{
	m_pKeyStates["Attack"].bKeyState = false;
}

void UCpt_KeyStateMng::KB_Dash_Down()
{
	if (m_pKeyStates["Dash"].bKeyState == false)
	{
		m_pKeyStates["Dash"].fPressTime = 0.0f;
	}
	m_pKeyStates["Dash"].bKeyState = true;
}

void UCpt_KeyStateMng::KB_Dash_Up()
{
	m_pKeyStates["Dash"].bKeyState = false;
}

void UCpt_KeyStateMng::KB_TraceDash_Down()
{
	if (m_pKeyStates["TraceDash"].bKeyState == false)
	{
		m_pKeyStates["TraceDash"].fPressTime = 0.0f;
	}
	m_pKeyStates["TraceDash"].bKeyState = true;
}

void UCpt_KeyStateMng::KB_TraceDash_Up()
{
	m_pKeyStates["TraceDash"].bKeyState = false;
}

void UCpt_KeyStateMng::KB_ComboAtk_Down()
{
	if (m_pKeyStates["ComboAtk"].bKeyState == false)
	{
		m_pKeyStates["ComboAtk"].fPressTime = 0.0f;
	}
	m_pKeyStates["ComboAtk"].bKeyState = true;
}

void UCpt_KeyStateMng::KB_ComboAtk_Up()
{
	m_pKeyStates["ComboAtk"].bKeyState = false;
}