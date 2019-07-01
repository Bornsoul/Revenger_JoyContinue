// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_DialogWidget.generated.h"

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FDialogue
{
	GENERATED_BODY();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
		bool m_bImageList_Random = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
		TArray<class UTexture2D*> m_pImgList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog Media")
		bool m_bUseMediaTexture = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog Media")
		class UMaterial* m_pMediaMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog Media")
		class UMediaSource* m_pMediaSource;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sSubName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sText;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_DialogWidget : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
		TArray<FDialogue> m_pDialogList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog Sub", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UWidget_DialogHUD> m_pInst_HudWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Dialog Sub", meta = (AllowPrivateAccess = "true"))
		class UWidget_DialogHUD* m_pDialogHUD;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	int32 m_nDialogIndex = 0;
	bool m_bActiveDialog = false;
	bool m_bDestory = false;

public:	
	UCpt_DialogWidget();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool Active_Dialog();
	
	UFUNCTION(BlueprintCallable)
		void DeActive_Dialog();
	
	UFUNCTION(BlueprintCallable)
		bool Active_NextDialog();

	UFUNCTION(BlueprintCallable)
		bool Skip_Dialog();

	UFUNCTION(BlueprintCallable)
		void SetDialogData(int32 nIndex);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActiveDialog() { return m_bActiveDialog; }
};
