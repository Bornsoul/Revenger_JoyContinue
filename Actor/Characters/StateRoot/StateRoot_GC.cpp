#include "StateRoot_GC.h"
#include "StateMng_GC.h"

UStateRoot_GC::UStateRoot_GC()
{
}

UStateRoot_GC::~UStateRoot_GC()
{
	m_pStateMng = nullptr;
}

void UStateRoot_GC::Init(class UStateMng_GC* pMng)
{
	m_pStateMng = pMng;
}

void UStateRoot_GC::Enter()
{
}

void UStateRoot_GC::Exit()
{
}

void UStateRoot_GC::Update(float fDeltaTime)
{
}

void UStateRoot_GC::StateMessage(FString sMessage)
{
}


AGameCharacter* UStateRoot_GC::GetRootCharacter()
{
	if (m_pStateMng == nullptr) return nullptr;
	return m_pStateMng->GetRootCharacter();
}

void UStateRoot_GC::ChangeState(int eState)
{
	if (m_pStateMng != nullptr) m_pStateMng->ChangeState(eState);
}
