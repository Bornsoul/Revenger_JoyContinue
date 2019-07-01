#include "MovePortal.h"
#include "Cpt_PortalArrow.h"
#include "Actor/Characters/Player/GC_Player.h"
#include "Actor/Characters/Player/GBox/GBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Engine/Public/EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"

AMovePortal::AMovePortal()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	m_pCollider->OnComponentBeginOverlap.AddDynamic(this, &AMovePortal::OnOverlapBegin);
	m_pCollider->OnComponentEndOverlap.AddDynamic(this, &AMovePortal::OnOverlapEnd);
	m_pCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_pCollider->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = m_pCollider;

	m_pPortal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pPortal->SetupAttachment(m_pCollider);

	m_pColliderPortal = CreateDefaultSubobject<USphereComponent>(TEXT("PortalCols"));
	m_pColliderPortal->SetCollisionProfileName(TEXT("NoCollision"));
	m_pColliderPortal->SetupAttachment(m_pCollider);

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));

}

void AMovePortal::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> pArray = GetComponentsByClass(UCpt_PortalArrow::StaticClass());
	for (int i = 0; i < pArray.Num(); i++)
	{
		UCpt_PortalArrow* pObj = Cast<UCpt_PortalArrow>(pArray[i]);
		if (pObj == nullptr) continue;
		m_pPortalArrow.Add(pObj);
	}

	m_pPlayer = nullptr;
	m_bActive = false;
	m_bGetIn = false;
	m_bUsed = false;

	m_fDestroyTime_End = m_fDestroyTime;

	m_vColliderSize = m_pCollider->GetScaledBoxExtent();	
	m_pCollider->SetBoxExtent(FVector(0.0f, 0.0f, 0.0f), false);
	if (m_bPortalActive == true)
		SpawnPortal();

	m_bJHActive = m_bPortalActive;
}

void AMovePortal::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pEndPortal = nullptr;
	m_pStartPortal = nullptr;
	m_bUsed = true;
	for (int i = 0; i < m_pPortalArrow.Num(); i++)
	{
		if (m_pPortalArrow[i] != nullptr)
		{
			m_pPortalArrow[i]->ConditionalBeginDestroy();
			m_pPortalArrow[i] = nullptr;
		}
	}
}

void AMovePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (m_bActive == false) return;

	/*if (m_bJHActive)
	{
		//m_pColliderPortal->SetCollisionResponseToChannel(ECC_Pawn, ECR_);
		m_pColliderPortal->SetCollisionProfileName(TEXT("BlockAll"));

	}
	else
	{
		m_pColliderPortal->SetCollisionProfileName(TEXT("NoCollision"));
	
		
	
	}*/
		


	if (m_bUseAndDestroy == true)
	{
		if (m_bDestroy == true)
		{
			m_fDestroyTime_Cur += DeltaTime;
			if (m_fDestroyTime_Cur >= m_fDestroyTime_End)
			{
				m_fDestroyTime_Cur = 0.0f;

				m_bDestroy = false;
				m_bActive = false;
				Destroy();
				ULOG(TEXT("%s is Destroy"), *GetName());
				return;
			}
		}
	}

	if (m_bGetIn)
	{
		if (m_pPlayer == nullptr) return;
		if (m_pStartPortal == nullptr && m_pEndPortal == nullptr)
		{
			for (int i = 0; i < m_pPortalArrow.Num(); i++)
			{
				if (m_pPortalArrow[i] != nullptr)
				{
					if (m_pStartPortal == nullptr)
					{
						if (m_pPortalArrow[i]->GetPortalNum() == m_nCurPortal)
						{
							m_pStartPortal = Cast<UCpt_PortalArrow>(m_pPortalArrow[i]);
						}
					}

					if (m_pEndPortal == nullptr)
					{
						if (m_pPortalArrow[i]->GetPortalNum() == m_nNextPortal)
						{
							m_pEndPortal = Cast<UCpt_PortalArrow>(m_pPortalArrow[i]);
						}
					}
				}
			}
		}

		if (m_pStartPortal != nullptr && m_pEndPortal != nullptr)
		{
			if (GetKeyStateMng()->GetKeyIsDown(EKeys::F))
			{
				m_pColliderPortal->SetVisibility(false);
				m_pColliderPortal->SetCollisionProfileName(TEXT("NoCollision"));
				if(m_pPlayer!=nullptr) m_pPlayer->Control_Portal(m_pStartPortal, m_pEndPortal);
				m_bGetIn = false;
				m_bDestroy = true;
				return;
			}
		}
	}
}

void AMovePortal::SpawnPortal()
{
	m_bActive = true;
	m_pCollider->SetBoxExtent(m_vColliderSize, true);
	m_pColliderPortal->SetCollisionProfileName(TEXT("BlockAll"));

}

void AMovePortal::SetCircleActive(bool bActive)
{
	m_bJHActive = bActive;
	//ULOG(TEXT("a"));
	if ( bActive )
		m_pColliderPortal->SetCollisionProfileName(TEXT("BlockAll"));		
	else
		m_pColliderPortal->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMovePortal::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bActive == false) return;
	m_bGetIn = true;

	//if (m_nNextPortal < 0) return;
	//if (m_pPortalArrow.Num() <= 0) return;

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (m_pPlayer != nullptr) return;
		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{			
			AGBox* pActor = Cast<AGBox>(OtherActor);
			if (pActor != nullptr)
			{		
							
				m_pPlayer = pActor;
					
				ULOG(TEXT("Portal Joy IN"));

				return;
			}
		}
	}
	
}

void AMovePortal::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{
			m_pColliderPortal->SetCollisionProfileName(TEXT("BlockAll"));

			m_bGetIn = false;
			ULOG(TEXT("Portal Joy Out"));
			return;
		}
	}

}