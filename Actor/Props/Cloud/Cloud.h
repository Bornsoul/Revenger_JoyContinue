// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "Cloud.generated.h"

UCLASS()
class REVENGER_API ACloud : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	UPROPERTY()
		class UCpt_WidgetDialog* m_pDialog;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Option, Meta = (AllowPrivateAccess = true))
		class TSubclassOf<class URes_DialogList> m_pInst_Dialog;

	UPROPERTY()
		class AGBox* m_pPlayer;

	UPROPERTY()
		class UCpt_StageIntro* m_pStageIntro;

	bool m_bFindPlayer = false;

	int m_nDialogGroup = 0;
	int m_nDialogIndex = 0;

	float m_fStartTime_Curr = 0.0f;
	float m_fStartTime_End = 1.5f;
	bool m_bStart = false;

	bool m_bDestroy = false;

public:
	UPROPERTY(EditAnywhere)
		FVector2D m_vStartEndTime = FVector2D(1.5f, 4.0f);

public:	
	// Sets default values for this actor's properties
	ACloud();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void DialogStart();
};
