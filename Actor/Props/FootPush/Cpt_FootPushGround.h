// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_FootPushGround.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class REVENGER_API UCpt_FootPushGround : public UActorComponent
{
	GENERATED_BODY()

private :	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		FVector m_vOriginLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		bool m_bPushState = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		float m_fPushDepth = 80.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_pMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		float m_fResetTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPush, meta = (AllowPrivateAccess = "true"))
		float m_fResetTime_Ago = 0.1f;
private :
	
	



public:	
	UCpt_FootPushGround();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Ground_Push_In();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
		void Ground_Push_Out();
};
