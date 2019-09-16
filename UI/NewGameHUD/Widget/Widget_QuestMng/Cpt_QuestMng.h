// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_QuestMng.generated.h"

UENUM(BlueprintType)
enum class eQuestIconState : uint8
{
	E_WORLD UMETA(DisplayName = "World"),
	E_QUEST UMETA(DisplayName = "Quest"),

	E_MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_QuestMng : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_QuestHud> m_pInst_Hud;

	UPROPERTY()
		TSubclassOf<class UWidget_QuestItem> m_pInst_Item;

	UPROPERTY()
		class UWidget_QuestHud* m_pHud;

	UPROPERTY()
		class UWidget_QuestItem* m_pWorldNameItem;

	UPROPERTY()
		TArray<class UWidget_QuestItem*> m_pItemList;

	UPROPERTY()
		APlayerController* m_pController;

public:	
	UCpt_QuestMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetVisible(bool bVisible);

	UFUNCTION(BlueprintCallable)
		void HideHud();

	UFUNCTION(BlueprintCallable)
		void ShowHud();
	
	UFUNCTION()
		void CreateHud(eQuestIconState eIconState, FText sText, FString sTag, const bool bQuest);

	UFUNCTION(BlueprintCallable)
		void CreateQuest(eQuestIconState eIconState, FText sText, FString sTag);
	
	UFUNCTION(BlueprintCallable)
		void CreateWorldName(eQuestIconState eIconState, FText sText);

	UFUNCTION(BlueprintCallable)
		void DoneQuest(FString sTagName);

	UFUNCTION(BlueprintCallable)
		void DoneQuest_Index(int32 nIndex);

	UFUNCTION(BlueprintCallable)
		void DoneQuest_All();

	UFUNCTION(BlueprintCallable)
		void RemoveQuest(FString sTagName);

	UFUNCTION(BlueprintCallable)
		void RemoveQuest_Index(int32 nIndex);

	UFUNCTION(BlueprintCallable)
		void RemoveQuest_All(const bool bIncludeDone = false);

	FORCEINLINE class UWidget_QuestItem* Add_Item(eQuestIconState eIconState, FText sText, FString sTag);
	FORCEINLINE class UWidget_QuestItem* Add_World(eQuestIconState eIconState, FText sText, FString sTag);
};
