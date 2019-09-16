// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSaveMng.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_GameSave.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_GameSave : public UActorComponent
{
	GENERATED_BODY()

private:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveMng", Meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UGameSaveMng> m_pInst_SaveData;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveMng", Meta = (AllowPrivateAccess = "true"))
		class UGameSaveMng* m_pGameSaveMng;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveMng", Meta = (AllowPrivateAccess = "true"))
		class UCpt_SaveDataAlert* m_pSaveDataAlert;

public:	
	UCpt_GameSave();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! Data Save
	UFUNCTION(BlueprintCallable, DisplayName = "데이터 저장", Category = "SaveData")
		bool Save_Data(const FString sDataName = "Test01", const int32 nIndex = 0, const float fAlertTime = 3.0f);

	//! Data Delete
	UFUNCTION(BlueprintCallable, DisplayName = "데이터 삭제", Category = "SaveData")
		bool Delete_Data(const FString sDataName = "Test01", const int32 nIndex = 0, const bool bCheckData = false);

	//! Data Load
	UFUNCTION(BlueprintCallable, DisplayName = "데이터 로드", Category = "SaveData")
		class UGameSaveMng* Load_Data(const FString sDataName = "Test01", const int32 nIndex = 0, const bool bCheckData = false);

	//! Data Exist Check
	UFUNCTION(BlueprintPure, DisplayName="데이터 체크", Category = "SaveData")
		bool CheckSaveData(const FString sDataName = "Test01", const int32 nIndex = 0);

	//! Data Exist And Create
	UFUNCTION(BlueprintCallable, DisplayName="데이터 체크 및 생성", Category = "SaveData")
		bool Check_DataValid();

	//! Data Variable
	UFUNCTION(BlueprintPure, Category = "SaveData")
		FORCEINLINE class UGameSaveMng* GetGameSaveMng() { return m_pGameSaveMng; }
};
