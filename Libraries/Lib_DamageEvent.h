// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/EngineTypes.h"

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Lib_DamageEvent.generated.h"

USTRUCT()
struct REVENGER_API FDamageEvent_Hit : public FDamageEvent
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		float m_fDamage;				//! 데미지

	UPROPERTY()
		FVector m_vAttackerLocaction;	//! 공격자의 위치

	UPROPERTY()
		FVector m_vHitPoint;			//! 맞은 좌표

	FDamageEvent_Hit()
		: m_fDamage(0.0f), m_vAttackerLocaction(FVector::ZeroVector), m_vHitPoint(FVector::ZeroVector)
	{}
	FDamageEvent_Hit(float fDamage, FVector vAttackerLocation, FVector vHitPoint)
		: m_fDamage(fDamage), m_vAttackerLocaction(vAttackerLocation), m_vHitPoint(vHitPoint)
	{}


	static const int32 ClassID = 3;		//! 공격 속성 ID값, 이 값으로 어떤 공격이 들어 왔는지 확인함

	virtual int32 GetTypeID() const override { return FDamageEvent_Hit::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FDamageEvent_Hit::ClassID == InID) || FDamageEvent::IsOfType(InID); };
};

USTRUCT()
struct REVENGER_API FDamageEvent_Parring : public FDamageEvent_Hit
{
	GENERATED_USTRUCT_BODY()

		FDamageEvent_Parring()
		: FDamageEvent_Hit(0.0f, FVector::ZeroVector, FVector::ZeroVector)
	{}
	FDamageEvent_Parring(float fDamage, FVector vAttackerLocation, FVector vHitPoint)
		: FDamageEvent_Hit(fDamage, vAttackerLocation, vHitPoint)
	{}


	static const int32 ClassID = 4;		//! 공격 속성 ID값, 이 값으로 어떤 공격이 들어 왔는지 확인함

	virtual int32 GetTypeID() const override { return FDamageEvent_Parring::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FDamageEvent_Parring::ClassID == InID) || FDamageEvent::IsOfType(InID); };
};

USTRUCT()
struct REVENGER_API FDamageEvent_Fatality : public FDamageEvent_Hit
{
	GENERATED_USTRUCT_BODY()

		FDamageEvent_Fatality()
		: FDamageEvent_Hit(0.0f, FVector::ZeroVector, FVector::ZeroVector)
	{}
	FDamageEvent_Fatality(float fDamage, FVector vAttackerLocation, FVector vHitPoint)
		: FDamageEvent_Hit(fDamage, vAttackerLocation, vHitPoint)
	{}


	static const int32 ClassID = 5;		//! 공격 속성 ID값, 이 값으로 어떤 공격이 들어 왔는지 확인함

	virtual int32 GetTypeID() const override { return FDamageEvent_Fatality::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FDamageEvent_Fatality::ClassID == InID) || FDamageEvent::IsOfType(InID); };
};

USTRUCT()
struct REVENGER_API FDamageEvent_KnockDown : public FDamageEvent_Hit
{
	GENERATED_USTRUCT_BODY()

		FDamageEvent_KnockDown()
		: FDamageEvent_Hit(0.0f, FVector::ZeroVector, FVector::ZeroVector)
	{}
	FDamageEvent_KnockDown(float fDamage, FVector vAttackerLocation, FVector vHitPoint)
		: FDamageEvent_Hit(fDamage, vAttackerLocation, vHitPoint)
	{}


	static const int32 ClassID = 6;		//! 공격 속성 ID값, 이 값으로 어떤 공격이 들어 왔는지 확인함

	virtual int32 GetTypeID() const override { return FDamageEvent_KnockDown::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FDamageEvent_KnockDown::ClassID == InID) || FDamageEvent::IsOfType(InID); };
};

UENUM()
enum class E_DamageEventClass : uint8
{
	E_Hit = 3,
	E_Parring = 4,
	E_Fatality = 5,
	E_KnockDown = 6,

	E_MAX,
};

UCLASS()
class REVENGER_API ULib_DamageEvent : public UObject
{
	GENERATED_BODY()

public:
	static E_DamageEventClass GetDamageEventClass(int32 nDamageEventID)
	{
		return (E_DamageEventClass)nDamageEventID;
	}
};

