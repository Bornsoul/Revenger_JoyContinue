// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_SimpleMenu.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_SimpleMenu : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_SimpleMenu> m_pInst_Widget;

	UPROPERTY()
		class UWidget_SimpleMenu* m_pWidget;

	bool m_bActive = false;

public:	
	UCpt_SimpleMenu();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Active_SimpleMenu();
	void DeActive_SimpleMenu();

	bool Menu_GetStart();
};
