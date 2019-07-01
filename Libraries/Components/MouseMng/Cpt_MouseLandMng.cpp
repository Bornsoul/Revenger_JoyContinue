// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_MouseLandMng.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "GameFrameWork/SpringArmComponent.h"

// Sets default values for this component's properties
UCpt_MouseLandMng::UCpt_MouseLandMng()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	m_pBox->SetupAttachment(this);
	m_pBox->SetBoxExtent(FVector(10000.0f, 10000.0f, 20.0f));
	m_pBox->SetCollisionProfileName(TEXT("MouseLand"));
	m_pBox->bHiddenInGame = true;
}


// Called when the game starts
void UCpt_MouseLandMng::BeginPlay()
{
	Super::BeginPlay();
	//m_pBox->SetBoxExtent(FVector(300.0f, 300.0f, 20.0f));
	m_vMouseLocation = FVector::ZeroVector; 
	
	UActorComponent* pFindCmp =  GetOwner()->GetComponentByClass(USpringArmComponent::StaticClass());
	if (pFindCmp != nullptr)
	{
		m_pOwnerSpringArm = Cast<USpringArmComponent>(pFindCmp);
		if (m_pOwnerSpringArm == nullptr)
		{
			ULOG(TEXT("Error m_pOwnerSpringArm is nullptr"));
		}
	}

	
}


// Called every frame
void UCpt_MouseLandMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Tick_Mouse();
	Tick_MouseMoveCam(DeltaTime);
}

FVector UCpt_MouseLandMng::GetMouse_Location()
{
	return m_vMouseLocation;
}

void UCpt_MouseLandMng::Tick_Mouse()
{
	FHitResult pHitResult;
	
	bool bResult = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_GameTraceChannel2, false, pHitResult);
	if (bResult == true)
	{
		m_vMouseLocation = pHitResult.ImpactPoint;
	}
}

void UCpt_MouseLandMng::Tick_MouseMoveCam(float fDeltaTime)
{
	if (m_pOwnerSpringArm == nullptr) return;
	FVector vCharPos = GetOwner()->GetActorLocation();
	FVector vMousePos = vCharPos;
	if (m_bMouseCamMoveActive == true)
	{
		vMousePos = GetMouse_Location();
	}

	
	vMousePos.Z = vCharPos.Z;

	FVector vSpringLoc = FMath::Lerp(vCharPos, vMousePos, 0.2f);
	/*float fDist = FVector::Dist(vSpringLoc, vCharPos);
	float fMaxDist = 250.0f;

	if (fDist > fMaxDist)
	{
		vSpringLoc = 
	}


	ULOG(TEXT("%f"), FVector::Dist(vSpringLoc, vCharPos));*/
	m_pOwnerSpringArm->SetWorldLocation(vSpringLoc);
}