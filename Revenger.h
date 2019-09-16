// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma warning(disable:4996)

#include "EngineMinimal.h"
#include "Engine/GameEngine.h"
#include "Libraries/Lib_DamageEvent.h"
#include "UI/Popup/Obj_AlertPopup.h"

DECLARE_LOG_CATEGORY_EXTERN(Revenger, Log, All);

#define ULOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ULOG_S() UE_LOG(Revenger, Warning, TEXT("%s"), *ULOG_CALLINFO)
#define ULOG(Format, ...) UE_LOG(Revenger, Warning, TEXT("%s %s"), *ULOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define UALERT(Format, ...) UObj_AlertPopup* pAlert = NewObject<UObj_AlertPopup>(this); if (pAlert != nullptr) {	ULOG(Format, ##__VA_ARGS__); pAlert->CreateAlert(FString::Printf(Format, ##__VA_ARGS__)); }


#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif