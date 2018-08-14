

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "ScitechHardwareInterface.generated.h"

/**
*
*/
UINTERFACE(MinimalAPI)
class UScitechHardwareInterface : public UInterface
{
	GENERATED_BODY()

	UScitechHardwareInterface(const class FObjectInitializer& ObjectInitializer);
};

class SCITECHHARDWARE_API IScitechHardwareInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Scitech Hardware Interface Events")
		void DigitalInputActivated(int32 InputIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Scitech Hardware Interface Events")
		void DigitalInputDeactivated(int32 InputIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Scitech Hardware Interface Events")
		void AnalogueInputChanged(int32 InputIndex, float value);
};
