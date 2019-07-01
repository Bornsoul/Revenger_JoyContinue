// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/SceneComponent.h"
#include "Cpt_MouseLandMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_MouseLandMng : public USceneComponent
{
	GENERATED_BODY()

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Box, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_pBox;

	UPROPERTY()
		class USpringArmComponent* m_pOwnerSpringArm;

	FVector m_vMouseLocation;

	bool m_bMouseCamMoveActive = false;

public:	
	UCpt_MouseLandMng();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
		FVector GetMouse_Location();

	UFUNCTION(BlueprintCallable)
		void SetMouseCamMove(bool bActive) {  m_bMouseCamMoveActive = bActive; }

private :
	void Tick_Mouse();

	void Tick_MouseMoveCam(float fDeltaTime);

};
