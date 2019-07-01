// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_EnemyHp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_EnemyHp : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UWidget_EnemyHp> m_pInst_Widget;

	UPROPERTY()
		TArray<class UWidget_EnemyHp*> m_pHpArray;

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpPos = FVector2D(30.0f, 250.0f);

	FVector m_vActorPos = FVector(0.0f, 0.0f, 0.0f);


	bool m_bActive = false;
	FVector2D m_vWidgetPos;

public:	
	UCpt_EnemyHp();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddHeart(AActor* pActor, int32 nHpCount);
	void SetHeartSize(FVector vPos, FVector2D vSize);
	void Tick_Position();

	void SetHit();
	void SetDestroy();
};
