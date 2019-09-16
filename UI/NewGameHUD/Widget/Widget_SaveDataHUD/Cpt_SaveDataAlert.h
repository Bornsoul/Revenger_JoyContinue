// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_SaveDataAlert.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_SaveDataAlert : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_SaveDataItem> m_pInst_Widget;

	UPROPERTY()
		TArray<class UWidget_SaveDataItem*> m_pSaveDataItem;

	UPROPERTY()
		class AHUD_Game* m_pHud;

	UPROPERTY()
		class APlayerController* m_pController;

	bool m_bDestroy = false;

public:	
	UCpt_SaveDataAlert();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		class UWidget_SaveDataItem* Create_Alert(float fAlertTime = 2.0f);

	UFUNCTION(BlueprintCallable)
		void Destroy_Alert(int nIndex = 0);

	UFUNCTION(BlueprintCallable)
		void DestroyAll_Alerts();

	FORCEINLINE void SetDestroyed(bool bDestroy) { m_bDestroy = bDestroy; }
	FORCEINLINE bool GetDestroyed() { return m_bDestroy; }
};
