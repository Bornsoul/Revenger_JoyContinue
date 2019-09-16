// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_DialogItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_DialogItem : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UImage* m_pImg_Icon;

	UPROPERTY()
		class URichTextBlock* m_pRich_Name;

	UPROPERTY()
		class URichTextBlock* m_pRich_Text;

	UPROPERTY()
		class UTextBlock* m_pTxt_Count;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		bool m_bImageList_Random = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		TArray<class UTexture2D*> m_pImgList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true", MultiLine = "true"))
		FText m_sName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true", MultiLine = "true"))
		FText m_sNameSub;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true", MultiLine = "true"))
		FText m_sText;

	bool m_bActive = false;
	bool m_bRevers = false;


	bool m_bStoryDialog = false;
	float m_fStoryDialog_Curr = 0.0f;
	float m_fStoryDialog_End = 0.055f;
	int32 m_nDialogStrLen = 0;
	FString m_sDialogText;
	FString m_sDialogAddText;


	/*float m_fLenTime_Curr = 0.0f;
	float m_fLenTime_End = 0.055f;
	int32 m_nStrLen = 0;
	bool m_bStr = false;

	FString m_sDialogStr;
	FString m_sAddStr;*/

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetCountText(int32 nCurIndex, int32 nMaxIndex);

	void SetDialogData(bool bRandom, TArray<class UTexture2D*> pTextures, FText sName, FText sNameSub, FText sText);
	void Execute_StringDialog(FString sDialog);
	bool Skip_Dialog();

	void Tick_StringDialog(float fDeltaTime);

	FORCEINLINE void SetDialogTextSpeed(float fSpeed = 0.055f) { m_fStoryDialog_End = fSpeed; }
	FORCEINLINE bool GetDialogPlaying() { return m_bStoryDialog; }
};
