// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_GameSave.h"
#include "UI/NewGameHUD/Widget/Widget_SaveDataHUD/Cpt_SaveDataAlert.h"
#include "Kismet/GameplayStatics.h"

UCpt_GameSave::UCpt_GameSave()
{
	PrimaryComponentTick.bCanEverTick = false;

	/*static ConstructorHelpers::FObjectFinder<UClass> Const_SaveData(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/SaveData/BP_GameSaveMng.BP_GameSaveMng_C"));
	if (Const_SaveData.Succeeded() ) 
	{
		m_pInst_SaveData = Const_SaveData.Object;
	}*/

	m_pSaveDataAlert = CreateDefaultSubobject<UCpt_SaveDataAlert>(TEXT("DataAlert"));
	if (m_pSaveDataAlert == nullptr)
	{
		ULOG(TEXT("SaveData Alert is nullptr"));
		return;
	}
}

void UCpt_GameSave::BeginPlay()
{
	Super::BeginPlay();

	m_pGameSaveMng = Cast<UGameSaveMng>(UGameplayStatics::CreateSaveGameObject(UGameSaveMng::StaticClass()));
	if (m_pGameSaveMng == nullptr)
	{
		ULOG(TEXT("GameSaveMng is nullptr"));		
		return;
	}

}

void UCpt_GameSave::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (m_pGameSaveMng != nullptr)
	{
		if (m_pGameSaveMng->IsValidLowLevel())
		{
			m_pGameSaveMng = nullptr;
		}
	}

	if (m_pSaveDataAlert != nullptr)
	{
		if (m_pSaveDataAlert->IsValidLowLevel())
		{
			m_pSaveDataAlert = nullptr;
		}
	}
}

void UCpt_GameSave::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UCpt_GameSave::Save_Data(const FString sDataName, const int32 nIndex, const float fAlertTime)
{
	if (sDataName.IsEmpty() || nIndex < 0)
	{
		UALERT(TEXT("Value is Empty"));
		return false;
	}

	if (m_pGameSaveMng == nullptr)
	{
		UALERT(TEXT("Manager is nullptr"));
		return false;
	}
	else
	{	
		m_pGameSaveMng->m_sSaveData_Name = sDataName;
		m_pGameSaveMng->m_nSaveData_Index = nIndex;
		UGameplayStatics::SaveGameToSlot(m_pGameSaveMng, sDataName, nIndex);

		if (fAlertTime >= 0.0f)
		{
			if (m_pSaveDataAlert != nullptr)
			{
				m_pSaveDataAlert->Create_Alert(fAlertTime);
			}
		}

		return true;
	}

	return false;
}

class UGameSaveMng* UCpt_GameSave::Load_Data(const FString sDataName, const int32 nIndex, const bool bCheckData)
{
	if (sDataName.IsEmpty() || nIndex < 0)
	{
		ULOG(TEXT("Value is Empty"));
		return nullptr;
	}

	if (bCheckData)
	{
		if (CheckSaveData(sDataName, nIndex) == false)
		{
			ULOG(TEXT("CheckSaveData is Fail"));
			return nullptr;
		}
	}

	UGameSaveMng* pObj = Cast<UGameSaveMng>(UGameplayStatics::CreateSaveGameObject(UGameSaveMng::StaticClass()));
	if (pObj != nullptr)
	{
		pObj = Cast<UGameSaveMng>(UGameplayStatics::LoadGameFromSlot(sDataName, nIndex));
		if (pObj == nullptr)
		{
			ULOG(TEXT("Load is Fail"));
			return nullptr;
		}
		else
		{
			m_pGameSaveMng = Cast<UGameSaveMng>(pObj);
			return pObj;
		}
	}

	return nullptr;
}

bool UCpt_GameSave::Delete_Data(const FString sDataName, const int32 nIndex, const bool bCheckData)
{
	if (sDataName.IsEmpty() || nIndex < 0)
	{
		ULOG(TEXT("Value is Empty"));
		return false;
	}

	if (bCheckData)
	{
		if (CheckSaveData(sDataName, nIndex) == false)
		{
			ULOG(TEXT("CheckSaveData is Fail"));
			return false;
		}
	}

	UGameplayStatics::DeleteGameInSlot(sDataName, nIndex);
	return true;
}

bool UCpt_GameSave::CheckSaveData(const FString sDataName, const int32 nIndex)
{
	if (m_pGameSaveMng == nullptr)
	{
		UALERT(TEXT("GameSaveMng is nullptr"));

		m_pGameSaveMng = Cast<UGameSaveMng>(UGameplayStatics::CreateSaveGameObject(UGameSaveMng::StaticClass()));
		
		CheckSaveData(sDataName, nIndex);
		return false;
	}

	if (sDataName.IsEmpty() || nIndex < 0)
	{
		ULOG(TEXT("Value is Empty"));
		return false;
	}

	UGameSaveMng* pObj = Cast<UGameSaveMng>(UGameplayStatics::CreateSaveGameObject(UGameSaveMng::StaticClass()));
	if (pObj != nullptr)
	{
		pObj = Cast<UGameSaveMng>(UGameplayStatics::LoadGameFromSlot(sDataName, nIndex));
		if (pObj == nullptr)
		{
			ULOG(TEXT("Load is Fail"));
			return false;
		}
		else
		{
			if (pObj->m_sSaveData_Name.IsEmpty() == false)
			{
				//ULOG(TEXT("Check Load is Done")); 
				return true;
			}
			else
			{
				ULOG(TEXT("Check Load is Done But SaveName is Empty!!!"));
				return false;
			}
		}
	}
	else
	{
		ULOG(TEXT("Obj is Nullptr"));
		return false;
	}

	return false;
}

bool UCpt_GameSave::Check_DataValid()
{
	if (m_pGameSaveMng == nullptr)
	{
		UALERT(TEXT("GameSaveMng is nullptr"));
		m_pGameSaveMng = Cast<UGameSaveMng>(UGameplayStatics::CreateSaveGameObject(UGameSaveMng::StaticClass()));
		
		Check_DataValid();
		return false;
	}

	if ( CheckSaveData() == false)		
	{		
		m_pGameSaveMng->SetDataInit();
		if (Save_Data() == true)
		{
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != TEXT("Stage_4"))
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage_4"), true);
				ULOG(TEXT("Go to the Menu"));
			}

			ULOG(TEXT("Data is Empty, Create SaveData!"));
			return false;
		}
	}
	else
	{
		return true;
	}

	return false;
}
