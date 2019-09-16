// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_KeyInputHUD.generated.h"

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FKeyInputName
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sOriginalName_Kor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sOriginalName_Eng;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
		class UTexture2D* m_pTexture;

};


UCLASS()
class REVENGER_API UWidget_KeyInputHUD : public UWidget_Root
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UHorizontalBox* m_pHoriBox;

	UPROPERTY()
		class UTextBlock* m_pTxt_Title;

	UPROPERTY()
		class UTextBlock* m_pTxt_SubTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UWidget_KeyInputItem> m_pInst_KeyItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		TArray<class UWidget_KeyInputItem*> m_pKeyItemList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property Str", meta = (AllowPrivateAccess = "true"))
		TArray<FKeyInputName> m_stInputName;

	bool m_bKeyInputSuccess = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UTexture2D* GetChangeKeyName(FText sKeyName);

	UFUNCTION(BlueprintCallable)
		void DestroyItemChild();

	UFUNCTION(BlueprintCallable)
		void SetTitleAndSubTitle(const FText sTitle, const FText sSubTitle);

	UFUNCTION(BlueprintCallable)
		class UWidget_KeyInputItem* Create_KeyItem(const FText sKeyName);

	//! 키입력 성공시
	UFUNCTION(BlueprintCallable)
		bool Success_KeyInput(const FText sKeyName);

	//! 키입력 실패시 되돌림
	UFUNCTION(BlueprintCallable)
		bool Fail_KeyInput(const FText sKeyName);


	UFUNCTION(BlueprintCallable)
		void SetKeyInputSuccess(bool bSuccess) { m_bKeyInputSuccess = bSuccess; }

	UFUNCTION(BlueprintPure)
		bool GetKeyInputSuccess() { return m_bKeyInputSuccess; }
};