// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OSIPin.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_OSIPin : public UUserWidget
{
	GENERATED_BODY()
private :
	UPROPERTY()
		class AGameCharacter* m_pTargetActor;

	UPROPERTY()
		class UImage* m_pIcon;

	UPROPERTY()
		class UImage* m_pArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		TArray<class UTexture2D*> m_pIconList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		TArray<class UTexture2D*> m_pArrowList;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetShow(bool bShow);

	// 0 = Àâ¸÷, 1 = º¸½º
	UFUNCTION()
		void SetChangeImage(int32 nIconState);

	void SetTargetActor(class AGameCharacter* pTargetActor) { m_pTargetActor = pTargetActor; }
	class AGameCharacter* GetTargetActor() { return m_pTargetActor; }

	FORCEINLINE UImage* GetIconImage() { return m_pIcon; }
};
