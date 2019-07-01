#include "Cpt_EnemyHp.h"
#include "UI/Enemy/HpSystem/Widget_EnemyHp.h"
#include "Actor/Characters/GameCharacter.h"
#include "Kismet/GameplayStatics.h"

UCpt_EnemyHp::UCpt_EnemyHp()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_EnemyHP.BP_EnemyHP_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}

void UCpt_EnemyHp::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCpt_EnemyHp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (int i = 0; i < m_pHpArray.Num(); i++)
	{
		m_pHpArray[i]->RemoveFromParent();
	}
	m_pHpArray.Empty();
}

void UCpt_EnemyHp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bActive == false) return;

	Tick_Position();
}

void UCpt_EnemyHp::AddHeart(AActor* pActor, int32 nHpCount)
{
	if (m_pInst_Widget == nullptr) return;

	for (int i = 0; i < nHpCount; i++)
	{
		APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UWidget_EnemyHp* pObj = CreateWidget<UWidget_EnemyHp>(pPlayerController, m_pInst_Widget);
		if (pObj != nullptr)
		{
			pObj->SetTarget(pActor);
			pObj->AddToViewport();
			m_pHpArray.Add(pObj);
		}
	}

	m_bActive = true;
}

void UCpt_EnemyHp::SetHeartSize(FVector vPos, FVector2D vSize)
{
	//m_vWidgetPos = vSize;
	m_vActorPos = vPos;
	m_vHpPos = vSize;
}

void UCpt_EnemyHp::Tick_Position()
{
	for (int i = 0; i < m_pHpArray.Num(); i++)
	{
		if (m_pHpArray[i] != nullptr) 
		{
			AActor* pActor = m_pHpArray[i]->GetTarget();

			if (pActor != nullptr)
			{
				FVector vPos = pActor->GetActorLocation();		
				vPos.X = vPos.X + m_vActorPos.X;
				vPos.Z = vPos.Z + m_vActorPos.Z;
				vPos.Y = vPos.Y + m_vActorPos.Y;
				

				APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

				FVector2D vScreenPos;

				FVector test = FVector(vPos.X - i * m_vHpPos.X, vPos.Y + i * m_vHpPos.Y, vPos.Z);
				pPlayerController->ProjectWorldLocationToScreen(test, vScreenPos);

				int32 nScreen_Width = 0.0f;
				int32 nScreen_Height = 0.0f;

				pPlayerController->GetViewportSize(nScreen_Width, nScreen_Height);

				int32 nScreenX = (int32)vScreenPos.X ;
				int32 nScreenY = (int32)vScreenPos.Y;

				m_pHpArray[i]->SetPositionInViewport(FVector2D(nScreenX, nScreenY));
			}
		}
	}
}

void UCpt_EnemyHp::SetHit()
{
	if (m_pHpArray[0]->GetIsHit() == true)
	{
		ULOG(TEXT("All Hit"));
		return;
	}

	for (int i = m_pHpArray.Num() - 1; i >= 0; i--)
	{
		if (m_pHpArray[i] != nullptr)
		{
			if (m_pHpArray[i]->GetIsHit() == false)
			{

				m_pHpArray[i]->SetHit();
				return;
			}
		}
	}
}

void UCpt_EnemyHp::SetDestroy()
{
	m_bActive = false;

	for (int i = 0; i < m_pHpArray.Num(); i++)
	{
		if (m_pHpArray[i] != nullptr)
		{
			m_pHpArray[i]->SetActive(false);
		}
	}
}