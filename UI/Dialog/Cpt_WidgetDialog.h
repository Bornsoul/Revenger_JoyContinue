// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_WidgetDialog.generated.h"

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FDialog
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		int32 m_nGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		FLinearColor m_cNameColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		FString m_sName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		FString m_sSubName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		FString m_sDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		class UTexture2D* m_pCharacterImg;

};

UENUM()
enum class E_DialogType : uint8
{
	E_TYPE_GROUP,
	E_TYPE_COLOR,
	E_TYPE_NAME,
	E_TYPE_SUBNAME,
	E_TYPE_DIALOG,

	E_MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_WidgetDialog : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Dialog, Meta = (AllowPrivateAccess = true))
		TArray<FDialog> m_pDialogList;

	UPROPERTY()
		TSubclassOf<class UWidget_Dialog> m_pInst_Widget;

	UPROPERTY()
		class UWidget_Dialog* m_pWidget;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;


	/*UPROPERTY()
		class URes_DialogList* m_pDialogList;*/

	bool m_bDialoging = false;

	int m_nDialogGroup = 0;
	int m_nDialogIndex = 0;

	float m_fStartTime_Curr = 0.0f;

public:	
	UCpt_WidgetDialog();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	void InitDialog();
	//void AddDialogList(FString sPath);
	//void AddDialogList(class TSubclassOf<class URes_DialogList> pList);

	UFUNCTION(BlueprintCallable)
		void SetDestroy();

	UFUNCTION(BlueprintCallable)
		bool PlayDialog(int32 nGroup = 0, int32 nStartIndex = 0);

	UFUNCTION(BlueprintCallable)
		bool DialogStart();

	bool SkipDialog();

	TArray<FString> GetDialogString(E_DialogType eType, int32 nGroup);
	TArray<UTexture2D*> GetDialogTexture(int32 nGroup);
	TArray<FLinearColor> GetDialogNameColor(int32 nGroup);

	int32 GetGroup_StringLenght(int32 nGroup);

	UFUNCTION(BlueprintPure)
		int32 GetDialogLenght();

	bool GetIsTyping();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActiveDialog() { return m_bDialoging; }	
};
