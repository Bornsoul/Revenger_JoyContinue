// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_GBox_Idle.h"
#include "States/State_GBox_Move.h"
#include "States/State_GBox_Dodge.h"
#include "States/State_GBox_Attack.h"
#include "States/State_GBox_Die.h"
#include "States/State_GBox_MoveDash.h"
#include "States/State_GBox_Landing.h"
#include "States/State_GBox_PortalJump.h"
#include "States/State_GBox_PortalFalling.h"
#include "States/State_GBox_SimpleMenu.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_GBox.generated.h"


UENUM()
enum class E_State_GBox : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Move UMETA(DisplayName = "Move"),
	E_Dodge UMETA(DisplayName = "Dodge"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_MoveDash UMETA(DisplayName = "MoveDash"),
	E_Die UMETA(DisplayName = "Die"),
	E_Landing UMETA(DisplayName = "Landing"),
	E_PortalJump UMETA(DisplayName = "PortalJump"),
	E_PortalFalling UMETA(DisplayName = "PortalFalling"),

	E_SimpleMenu UMETA(DisplayName = "SimpleMenu"),


	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_GBox : public UStateMng_GC
{
	GENERATED_BODY()
	
private :
	UPROPERTY()
		class AGBox* m_pRootCharacter_Override;

public :
	UStateMng_GBox();
	virtual ~UStateMng_GBox();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AGBox* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
