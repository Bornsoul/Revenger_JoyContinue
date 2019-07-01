#include "Cpt_MouseMng.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UCpt_MouseMng::UCpt_MouseMng()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_MouseMng::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCpt_MouseMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Tick_Mouse();
}

void UCpt_MouseMng::Tick_Mouse()
{
	m_bMouseTraceSuccess = GetInfo_MouseAuto(&m_vMouseLocation, &m_rMouseTraceNormal);
}

bool UCpt_MouseMng::GetInfo_MouseAuto(FVector* vLocation, FRotator* rRotator)
{
	FHitResult pHitResult;
	bool bResult = MouseClickLineTrace(&pHitResult);
	if (bResult == true)
	{
		*vLocation = pHitResult.ImpactPoint;
		*rRotator = pHitResult.ImpactNormal.ToOrientationRotator();
	}
	return bResult;
}

bool UCpt_MouseMng::GetInfo_MouseClick(FVector* vLocation, FRotator* rRotator)
{
	FHitResult pHitResult;

	bool bResult = MouseClickLineTrace(&pHitResult);
	if (bResult == true)
	{
		*vLocation = pHitResult.ImpactPoint;
		*rRotator = pHitResult.ImpactNormal.ToOrientationRotator();

		AActor* pHitActor = pHitResult.GetActor();
		if (pHitActor != nullptr)
		{
			if (pHitActor->ActorHasTag(FName(TEXT("Enemy"))) == true)
			{
				*vLocation = pHitActor->GetActorLocation();
			}
		}
	}
	return bResult;
}

bool UCpt_MouseMng::MouseClickLineTrace(FHitResult* pHitResult)
{//ECC_Visibility  //ECC_GameTraceChannel1
	bool bResult = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, *pHitResult);

	return bResult;
}

bool UCpt_MouseMng::GetMouse_Location2(FVector& WorldLocation, FVector& WorldDirection)
{
	//FVector mouseLocation, mouseDirection;
	APlayerController* playerController = (APlayerController*)GetWorld()->GetFirstPlayerController();
	return playerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	
}