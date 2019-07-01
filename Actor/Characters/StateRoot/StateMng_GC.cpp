#include "StateMng_GC.h"
#include "StateRoot_GC.h"

UStateMng_GC::UStateMng_GC()
{

}

UStateMng_GC::~UStateMng_GC()
{
	Destroy();
}

void UStateMng_GC::Init(class AGameCharacter* pRoot)
{
	m_bDestroyed = false;
	m_pRootCharacter = pRoot;
	m_pCurrentState = nullptr;
}

void UStateMng_GC::Destroy()
{
	if (m_bDestroyed == true) return;
	

	/*for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{		
		it->Value->Exit();
		it->Value->ConditionalBeginDestroy();
	}*/
	m_pRootCharacter = nullptr;
	m_pCurrentState = nullptr;
	m_pStateClass.Empty();

	m_pRootCharacter = nullptr;
	m_pCurrentState = nullptr;
	m_bDestroyed = true;
}

void UStateMng_GC::Update(float fDeltaTime)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(fDeltaTime);
	}
}

void UStateMng_GC::ChangeState(int eState)
{
	m_eState = eState;
	
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}

UStateRoot_GC* UStateMng_GC::GetStateClassRef(int eFindState)
{
	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eFindState)
		{
			return it->Value;
		}
	}
	return nullptr;
}

void UStateMng_GC::StateMessage(FString sMessage)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->StateMessage(sMessage);
	}
}