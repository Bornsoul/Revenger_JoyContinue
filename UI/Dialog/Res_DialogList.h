// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Res_DialogList.generated.h"


//USTRUCT(Atomic, BlueprintType)
//struct REVENGER_API FDialog
//{
//	GENERATED_BODY();
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		int32 m_nGroup;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		FLinearColor m_cNameColor;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		FString m_sName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		FString m_sSubName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		FString m_sDialog;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
//		class UTexture2D* m_pCharacterImg;
//
//};

UCLASS(Blueprintable)
class REVENGER_API URes_DialogList : public UObject
{
	GENERATED_BODY()
	
//private:
//	UPROPERTY(EditDefaultsOnly, Category = Dialog, Meta = (AllowPrivateAccess = true))
//		TArray<FDialog> m_pDialogList;
//
//public:
//	TArray<FDialog> GetDialogList() { return m_pDialogList;  }
};
