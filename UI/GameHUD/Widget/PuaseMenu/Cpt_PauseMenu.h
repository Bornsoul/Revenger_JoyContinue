// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_PauseMenu.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_PauseMenu : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_PauseMenu> m_pInst_Widget;

	UPROPERTY()
		class UWidget_PauseMenu* m_pWidget;

	bool m_bActive = false;

public:
	UCpt_PauseMenu();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Active_PauseMenu();
	void DeActive_PauseMenu();

	bool GetActive() { return m_bActive; }
	bool GetAniPlaying();
	//bool Menu_GetResume();
	int32 Menu_GetButton();
};
