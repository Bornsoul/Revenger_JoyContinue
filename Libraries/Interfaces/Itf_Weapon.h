#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Itf_Weapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItf_Weapon : public UInterface
{
	GENERATED_BODY()
};

class REVENGER_API IItf_Weapon
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ItfWeapon")
		void Inter_Stiffen(float fTime, float fStiffenScale);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ItfWeapon")
		void Inter_Hit(class AActor* pActor);
};
