// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestAlarmHUD.generated.h"

UENUM(BlueprintType)
enum class eQuestIcon : uint8
{
	E_LOCATION UMETA(DisplayName = "Location"),
	E_QUEST UMETA(DisplayName = "Quest"),

	E_MAX,
};

USTRUCT(atomic, BlueprintType)
struct FQuestIcon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		eQuestIcon eIconType;

	UPROPERTY(EditAnywhere)
		UTexture2D* m_pIconImage;
};

UCLASS()
class REVENGER_API UWidget_QuestAlarmHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UVerticalBox* m_pVert_ItemList;

	UPROPERTY(EditAnywhere, Category = "ItemOption", meta = (AllowPrivateAccess = "true"))
		TArray<FQuestIcon> m_pIconList;

	UPROPERTY()
		TArray<class UWidget_QuestAlarm_Item*> m_pQuestItem;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidget_QuestAlarm_Item> m_pInst_QuestItem;

	UPROPERTY()
		class UWidget_QuestAlarm_Item* m_pWorldItem;

	bool m_bActive = false;
	bool m_bRevers = false;
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);
	
	UFUNCTION(BlueprintCallable)
		void SetWorldName(eQuestIcon eIcon, FText sText);


	UFUNCTION(BlueprintCallable)
		void Add_Quest(eQuestIcon eIcon, FText sText);


	UFUNCTION(BlueprintCallable)
		void Done_Quest(int nIndex = 0, float fDestroyDelay = 0.0f);


	UFUNCTION(BlueprintCallable)
		void Destroy_Quest(int nIndex = 0, float fDestroyDelay = 0.0f);

	UFUNCTION(BlueprintPure)
		bool DestroyAll_Quest();

	UFUNCTION(BlueprintPure)
		int32 GetQuestItemNum() { return m_pQuestItem.Num(); }

	void SetAlarmItemRoot(const TSubclassOf<UWidget_QuestAlarm_Item> pInstWidget);

	FORCEINLINE class UTexture2D* GetQuestIcon(eQuestIcon eIcon);
};