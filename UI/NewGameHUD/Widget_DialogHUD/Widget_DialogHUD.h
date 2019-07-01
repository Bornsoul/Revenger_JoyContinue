// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_DialogHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_DialogHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UWidget_DialogItem* m_pDialogItem;

	UPROPERTY()
		class UImage* m_pImg_Media;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WidgetOption", meta = (AllowPrivateAccess = "true"))
		class UMediaPlayer* m_pMediaPlayer;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetDialogData(bool bRandom, TArray<class UTexture2D*> pTextures, FText sName, FText sNameSub, FText sText);

	void SetMediaData(class UMaterial* pMat, class UMediaSource* pMediaSource);

	UFUNCTION(BlueprintCallable)
		void Skip_Dialog();

	FORCEINLINE bool GetActive() { return m_bActive; }
	bool GetIsPlaying();
};
