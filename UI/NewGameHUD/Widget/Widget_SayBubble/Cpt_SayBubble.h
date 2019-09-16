// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_SayBubble.generated.h"

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FSayBubble
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		FText m_sSaying;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
		float m_fSayDestroyDelay;

};

UENUM(BlueprintType)
enum class eSayState : uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_SHOW UMETA(DisplayName = "Show"),
	E_HIDE UMETA(DisplayName = "Hid"),
	E_WAIT UMETA(DisplayName = "Wait"),

	E_MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_SayBubble : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_SayDialogItem> m_pInst_SayDialog;

	UPROPERTY()
		class UWidget_SayDialogItem* m_pSayDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", Meta = (AllowPrivateAccess = "true"))
		bool m_bAutoStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option", Meta=(AllowPrivateAccess = "true"))
		bool m_bSayingIsRandom = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", Meta = (AllowPrivateAccess = "true"))
		float m_fSayTurnDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", Meta = (AllowPrivateAccess = "true"))
		TArray<FSayBubble> m_stSayBubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option Sub", Meta = (AllowPrivateAccess = "true"))
		FVector2D m_vBubbleLocation;

	int32 m_nSayIndex = 0;
	float m_fTurnDelay_Time = 0.0f;
	eSayState m_eState;

	bool m_bStopPlaying = false;

	bool m_bActive = false;
	
public:	
	UCpt_SayBubble();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetHidden(bool bHide);

	UFUNCTION(BlueprintCallable)
		void PlaySaying();

	UFUNCTION(BlueprintCallable)
		void StopSaying();

	UFUNCTION(BlueprintPure)
		bool GetHideAniEnd();

	UFUNCTION(BlueprintCallable)
		void SetTarget(class AActor* pTarget);
	
	UFUNCTION(BlueprintCallable)
		void SetAutoPlay(bool bPlay);

	void Show_SayDialog();
	void Hide_SayDialog();

public:
	UFUNCTION(BlueprintPure)
		class UWidget_SayDialogItem* GetSayDialog() { return m_pSayDialog; }

};
