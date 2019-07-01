// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_ParticleMng.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_ParticleMng : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Particles", Meta = (AllowPrivateAccess = true))
		TMap<FString, class UParticleSystem*> m_pParticle_List;

public:
	UCpt_ParticleMng();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//! Cascade파티클 파일 가져오기 
	//! FString sName : 사용할 이름
	//! FString sPath : 파일 경로
	void AddParticleInstance(FString sName, FString sPath);

	//! 파티클 소환-좌표
	//! FString sParticleName			 : 등록한 이름 
	//! UObject* WorldContextObject		 : GetWorld()넣기
	//! FVector SpawnLocation			 : 소환할 월드 좌표
	//! FRotator SpawnRotation			 : 소환할때 Rotation
	//! FVector SpawnScale				 : 소환할때 Scale
	//! bool bAutoDestroy				 : true하면 Loop가 안되는 Cacade이펙트는 자동으로 Destroy됨
	//! return							 : 소환된 이펙트 엑터 
	class UParticleSystemComponent* SpawnParticleAtLocation(FString sParticleName, const UObject* WorldContextObject, FVector SpawnLocation, FRotator SpawnRotation = FRotator::ZeroRotator, FVector SpawnScale = FVector::OneVector, bool bAutoDestroy = true);

	//! 파티클 소환 - Component에 붙여서(예 : 손에 파티클 붙이기)
	//! FString sParticleName				 : 등록한 이름 
	//! USceneComponent* pComponent			 : Attach할 Component(예 : USkeletalMesh)
	//! FName sSocketName					 : SkeletalMesh내부의 스켈레톤 소켓 이름
	//! FVector SpawnLocation				 : 소환할 월드 좌표
	//! FRotator SpawnRotation				 : 소환할때 Rotation
	//! FVector SpawnScale					 : 소환할때 Scale
	//! EAttachLocation::Type LocationType	 : Attach속성
	//! bool bAutoDestroy					 : true하면 Loop가 안되는 Cacade이펙트는 자동으로 Destroy됨
	//! return								 : 소환된 이펙트 엑터 
	class UParticleSystemComponent* SpawnParticleAttachComponent(FString sParticleName, USceneComponent* pComponent, FName sSocketName = NAME_None, FVector SpawnLocation = FVector::ZeroVector, FRotator SpawnRotation = FRotator::ZeroRotator, FVector SpawnScale = FVector::OneVector, EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bAutoDestroy = true);


	//! TMap에 있는 파티클 Instacne 가져오기
	//! FString sParticleName : 등록한 이름
	class UParticleSystem* GetParticleInstance(FString sParticleName);


};
