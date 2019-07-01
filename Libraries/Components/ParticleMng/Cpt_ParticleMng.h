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

	//! Cascade��ƼŬ ���� �������� 
	//! FString sName : ����� �̸�
	//! FString sPath : ���� ���
	void AddParticleInstance(FString sName, FString sPath);

	//! ��ƼŬ ��ȯ-��ǥ
	//! FString sParticleName			 : ����� �̸� 
	//! UObject* WorldContextObject		 : GetWorld()�ֱ�
	//! FVector SpawnLocation			 : ��ȯ�� ���� ��ǥ
	//! FRotator SpawnRotation			 : ��ȯ�Ҷ� Rotation
	//! FVector SpawnScale				 : ��ȯ�Ҷ� Scale
	//! bool bAutoDestroy				 : true�ϸ� Loop�� �ȵǴ� Cacade����Ʈ�� �ڵ����� Destroy��
	//! return							 : ��ȯ�� ����Ʈ ���� 
	class UParticleSystemComponent* SpawnParticleAtLocation(FString sParticleName, const UObject* WorldContextObject, FVector SpawnLocation, FRotator SpawnRotation = FRotator::ZeroRotator, FVector SpawnScale = FVector::OneVector, bool bAutoDestroy = true);

	//! ��ƼŬ ��ȯ - Component�� �ٿ���(�� : �տ� ��ƼŬ ���̱�)
	//! FString sParticleName				 : ����� �̸� 
	//! USceneComponent* pComponent			 : Attach�� Component(�� : USkeletalMesh)
	//! FName sSocketName					 : SkeletalMesh������ ���̷��� ���� �̸�
	//! FVector SpawnLocation				 : ��ȯ�� ���� ��ǥ
	//! FRotator SpawnRotation				 : ��ȯ�Ҷ� Rotation
	//! FVector SpawnScale					 : ��ȯ�Ҷ� Scale
	//! EAttachLocation::Type LocationType	 : Attach�Ӽ�
	//! bool bAutoDestroy					 : true�ϸ� Loop�� �ȵǴ� Cacade����Ʈ�� �ڵ����� Destroy��
	//! return								 : ��ȯ�� ����Ʈ ���� 
	class UParticleSystemComponent* SpawnParticleAttachComponent(FString sParticleName, USceneComponent* pComponent, FName sSocketName = NAME_None, FVector SpawnLocation = FVector::ZeroVector, FRotator SpawnRotation = FRotator::ZeroRotator, FVector SpawnScale = FVector::OneVector, EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bAutoDestroy = true);


	//! TMap�� �ִ� ��ƼŬ Instacne ��������
	//! FString sParticleName : ����� �̸�
	class UParticleSystem* GetParticleInstance(FString sParticleName);


};
