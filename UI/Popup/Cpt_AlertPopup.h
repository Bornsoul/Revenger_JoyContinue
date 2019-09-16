// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_AlertPopup.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_AlertPopup : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_AlertPopup> m_pInst_Alert;

	UPROPERTY()
		TSubclassOf<class UWidget_AlertHud> m_pInst_AlertHud;

	UPROPERTY()
		class UWidget_AlertPopup* m_pAlertPop;

	UPROPERTY()
		class UWidget_AlertHud* m_pAlertHud;

	bool m_bCreated = false;
	float m_fDestroyTime = 0.0f;
	float m_fCreatedTime = 0.0f;

public:	
	UCpt_AlertPopup();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void CreateAlert(const FString sText, const float fDestroyTime = 5.0f);

	class UWidget_AlertPopup* Add_Alert(const FString sText, const float fDestroyTime = 5.0f);

	UFUNCTION(BlueprintPure)
		bool GetIsCreated() { return m_bCreated; }
};
