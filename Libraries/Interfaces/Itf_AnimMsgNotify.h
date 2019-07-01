// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Itf_AnimMsgNotify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItf_AnimMsgNotify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REVENGER_API IItf_AnimMsgNotify
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimNotifyMessage")
		void Inter_Notify_Message(FName sMessage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimNotifyMessage")
		void Inter_Notify_SoundMessage(FName sMessage);

};
