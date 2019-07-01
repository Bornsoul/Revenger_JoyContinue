// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_MouseMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_MouseMng : public UActorComponent
{
	GENERATED_BODY()

private:
	FVector m_vMouseLocation;
	FRotator m_rMouseTraceNormal;
	bool m_bMouseTraceSuccess = false;

public:
	UCpt_MouseMng();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetMouseIsOnTrace() { return m_bMouseTraceSuccess; }
	FVector GetMouse_Location() { return m_vMouseLocation; }
	FRotator GetMouse_Rotator() { return m_rMouseTraceNormal; }

	bool GetMouse_Location2(FVector& WorldLocation, FVector& WorldDirection);

private:
	void Tick_Mouse();

	bool GetInfo_MouseAuto(FVector* vLocation, FRotator* rRotator);
	bool MouseClickLineTrace(FHitResult* pHitResult);

	bool GetInfo_MouseClick(FVector* vLocation, FRotator* rRotator);
};
