// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_KeyInputMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_KeyInputMng : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_KeyInputHUD> m_pInst_InputHud;

	UPROPERTY()
		class UWidget_KeyInputHUD* m_pKeyInputHud;

	UPROPERTY()
		TArray<FKey> m_stKeyList;

	UPROPERTY()
		TArray<FKey> m_stCreateKeyList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		float m_fRemoveHud_Time = 2.0f;

	bool m_bCreatedKey = false;
	float m_fRemoveHud = 0.0f;

	bool m_bSuccess = false;
	bool m_bEndComponent = false;

public:	
	UCpt_KeyInputMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! 제목과 부재를 설정
	void SetTitleAndSubTitle(const FText sTitle, const FText sSubTitle);

	//! 키입력 아이콘을 띄움
	bool Create_InputKey(const FKey stKey);

	//! 키를 입력 정보를 체크	
	UFUNCTION(BlueprintCallable)
		bool Press_Inputkey(const FText sKeyName);

	UFUNCTION(BlueprintCallable)
		bool Press_Inputkeys(const TArray<FKey> sKeyNameList);


	UFUNCTION(BlueprintCallable)
		bool Refresh_InputKeys();

	UFUNCTION(BlueprintCallable)
		bool Refresh_InputKey(const FKey stKey);

	//! 제목, 부재 및 키입력 아이콘 소환
	UFUNCTION(BlueprintCallable)
		void Create_InputKeySubTitle(const FText sTitle, const FText sSubTitle, const TArray<FKey> stKeyList, const float fRemoveTime = -1.0f, const bool bEndComp = true);


	//! True 입력하면 키입력이 완료된것으로 판정
	UFUNCTION(BlueprintCallable)
		void SetSuccess(bool bSuccess) { m_bSuccess = bSuccess; }

	//! 키입력이 모두 완료되면 True 반환
	UFUNCTION(BlueprintPure)
		bool GetSuccess(); // { return m_bSuccess; }

	UFUNCTION(BlueprintCallable)
		void SetKeepEndComp(bool bEndComp) { m_bEndComponent = bEndComp; }

	UFUNCTION(BlueprintPure)
		bool GetKeepEndComp() { return m_bEndComponent; }

	UFUNCTION(BlueprintPure)
		TArray<FKey> GetCreateKey() { return m_stCreateKeyList; }

};
