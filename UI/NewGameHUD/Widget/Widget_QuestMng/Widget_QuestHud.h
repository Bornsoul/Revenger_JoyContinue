// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cpt_QuestMng.h"

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_QuestHud.generated.h"

enum class eQuestIconState : uint8;

USTRUCT(atomic, BlueprintType)
struct FQuestIconList
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		eQuestIconState eIconType;

	UPROPERTY(EditAnywhere)
		UTexture2D* m_pIconImage;
};

UCLASS()
class REVENGER_API UWidget_QuestHud : public UWidget_Root
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		TArray<FQuestIconList> m_pIconList;

	UPROPERTY()
		class UVerticalBox* m_pVert_World;

	UPROPERTY()
		class UVerticalBox* m_pVert_Item;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	void Add_WorldList(class UWidget_QuestItem* pItem);
	void Add_ItemList(class UWidget_QuestItem* pItem);

	void Remove_ItemList(class UWidget_QuestItem* pItem);
	void Remove_ItemListIndex(int32 nIndex);

};
