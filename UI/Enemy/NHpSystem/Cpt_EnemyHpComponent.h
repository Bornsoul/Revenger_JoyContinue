// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_EnemyHpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_EnemyHpComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
		TSubclassOf<class UWidget_EnemyHpHUD> m_pInst_Hud;

	UPROPERTY()
		TSubclassOf<class UWidget_EnemyHpItem> m_pInst_Item;

	UPROPERTY()
		class UWidget_EnemyHpHUD* m_pHud;

	UPROPERTY()
		TArray<class UWidget_EnemyHpItem*> m_pHpItemList;

	UPROPERTY()
		class APlayerController* m_pController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		FVector2D m_vHudLocation;


public:	
	UCpt_EnemyHpComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void CreateHp(const float fHp);

	UFUNCTION(BlueprintCallable)
		void Hit();

	UFUNCTION(BlueprintCallable)
		void Heal();

	//UPROPERTY(BlueprintCallable)
		class UWidget_EnemyHpItem* Add_Hp();

	UFUNCTION(BlueprintCallable)
		void SetHudTarget(AActor* pActorTarget);

	UFUNCTION(BlueprintCallable)
		void SetHudLocation(FVector2D vLocation);

	UFUNCTION(BlueprintCallable)
		void DestroyHud();

	void Tick_HudTarget();
};
