// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_WarningSpace.h"
#include "WarningSpace_Circle.h"

// Sets default values for this component's properties
UCpt_WarningSpace::UCpt_WarningSpace()
{
	PrimaryComponentTick.bCanEverTick = true;

	
	Add_WarningSpace(TEXT("Circle"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/WarningSpace/BP_WarningSpace_Circle.BP_WarningSpace_Circle_C"));
	Add_WarningSpace(TEXT("Dash"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/WarningSpace/BP_WarningSpace_Dash.BP_WarningSpace_Dash_C"));
}


// Called when the game starts
void UCpt_WarningSpace::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_WarningSpace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

// Called every frame
void UCpt_WarningSpace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCpt_WarningSpace::Add_WarningSpace(FString sName, FString sPath)
{
	ConstructorHelpers::FClassFinder<AWarningSpace_Root> Asset_Effect(*sPath);
	if (Asset_Effect.Succeeded())
	{
		m_pList.Add(sName, Asset_Effect.Class);
	}
	else
	{
		ULOG(TEXT("ObjectFind Fail"));
	}
}

AWarningSpace_Root* UCpt_WarningSpace::SpawnSpace_Circle(float fWarningTime, float fAngle, FVector vLocation, FRotator vRotation, FVector vScale)
{
	TSubclassOf<class AWarningSpace_Root> pFindObj = nullptr;
	for (TMap<FString, TSubclassOf<class AWarningSpace_Root>>::TIterator it = m_pList.CreateIterator(); it; ++it)
	{
		if (it->Key == TEXT("Circle"))
		{
			pFindObj = it->Value;
		}
	}
	if (pFindObj == nullptr) return nullptr;

	AWarningSpace_Circle* pBullet = GetWorld()->SpawnActor<AWarningSpace_Circle>(pFindObj);
	if (pBullet == nullptr) return nullptr;

	pBullet->SpawnSpace_Circle(fWarningTime, fAngle, vLocation, vRotation, vScale);

	return pBullet;
}

AWarningSpace_Root* UCpt_WarningSpace::SpawnSpace_Dash(float fWarningTime, FVector vLocation, FRotator vRotation, FVector vScale)
{
	TSubclassOf<class AWarningSpace_Root> pFindObj = nullptr;
	for (TMap<FString, TSubclassOf<class AWarningSpace_Root>>::TIterator it = m_pList.CreateIterator(); it; ++it)
	{
		if (it->Key == TEXT("Dash"))
		{
			pFindObj = it->Value;
		}
	}
	if (pFindObj == nullptr) return nullptr;

	AWarningSpace_Root* pBullet = GetWorld()->SpawnActor<AWarningSpace_Root>(pFindObj);
	if (pBullet == nullptr) return nullptr;

	pBullet->SpawnSpace(fWarningTime, vLocation, vRotation, vScale);

	return pBullet;
}