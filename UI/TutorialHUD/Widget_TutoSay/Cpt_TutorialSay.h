// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_TutorialSay.generated.h"

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FTutorialSay
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog", meta = (MultiLine = "true"))
		TArray<FText> m_sSayingList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
		TArray<float> m_fSayDelay;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_TutorialSay : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_TutoSayHUD> m_pInst_Hud;

	UPROPERTY()
		class UWidget_TutoSayHUD* m_pTutoSayHud;
	
	UPROPERTY()
		class UCpt_SoundMng* m_pSound;

	bool m_bPlaySay = false;

public:	
	UCpt_TutorialSay();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Create_TutoSay(const FTutorialSay stSayDialog);

	UFUNCTION(BlueprintCallable)
		void Stop_TutoSay();

	UFUNCTION(BlueprintPure)
		bool GetPlaySaying() { return m_bPlaySay; }

};
