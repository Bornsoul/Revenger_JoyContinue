// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputCoreTypes.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_KeyStateMng.generated.h"

struct ST_KeyStateMng
{
	bool bKeyState;
	float fPressTime;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_KeyStateMng : public UActorComponent
{
	GENERATED_BODY()

public:
	FVector2D m_vKeyInput;

	UPROPERTY()
		class AActor* m_pOwner;

	TMap<FString, ST_KeyStateMng> m_pKeyStates;

private:
	void AddKeyState(FString sStr);

public:
	UCpt_KeyStateMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	bool GetAnyKeyIsDown();

	UFUNCTION(BlueprintCallable)
	bool GetKeyIsDown(const FKey Key);

	UFUNCTION(BlueprintCallable)

	bool GetKeyIsJustPress(const FKey Key);

	UFUNCTION(BlueprintCallable)
	bool GetKeyIsJustRelease(const FKey Key);

public:
	void KB_Forward(float fValue);
	void KB_Right(float fValue);

	void KB_Attack_Down();
	void KB_Attack_Up();

	void KB_Dash_Down();
	void KB_Dash_Up();

	void KB_TraceDash_Down();
	void KB_TraceDash_Up();

	void KB_ComboAtk_Down();
	void KB_ComboAtk_Up();

public:
	FORCEINLINE FVector2D GetKeyInput() { return m_vKeyInput; }
};
