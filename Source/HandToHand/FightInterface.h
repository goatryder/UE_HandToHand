#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "UObject/Interface.h"
#include "FightInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UFightInterface: public UInterface
{

	GENERATED_BODY()

};


class IFightInterface
{

	GENERATED_BODY()

public:
	/* Add function declartation here */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attacks")
		void CheckPunch(bool IsLeftHand);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attacks")
		void CheckKick(bool IsLeftLeg);

};