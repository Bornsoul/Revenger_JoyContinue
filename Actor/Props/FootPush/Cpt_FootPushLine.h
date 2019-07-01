// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_FootPushLine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_FootPushLine : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY()
		TArray<FString> m_pBoneList;


	UPROPERTY()
		class USkeletalMeshComponent* m_pMesh;

	UPROPERTY()
		class UCapsuleComponent* m_pCapsule;

private :
	float m_fDefaultHeight;
	FVector m_vDefaultMeshLoc;


public:	
	UCpt_FootPushLine();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	void SetSKMesh(class AGameCharacter* pChar);
	void AddBone(FString sBoneName);

		
private :
	void Tick_PushLine(float fDeltaTime);

};
