

#pragma once

#include "CoreMinimal.h"
#include "ObjectMacros.h"
#include "NoExportTypes.h"
#include "SerialCommsState.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SCITECHHARDWARE_API USerialCommsState : public UObject
{
	GENERATED_BODY()

		USerialCommsState(const FObjectInitializer& ObjectInitializer);
public:
	bool DigitalInput1 = false;
	bool DigitalInput2 = false;
	bool DigitalInput3 = false;
	bool DigitalInput4 = false;
	bool DigitalInput5 = false;
	bool DigitalInput6 = false;
	bool DigitalInput7 = false;
	bool DigitalInput8 = false;
	bool DigitalInput9 = false;
	bool DigitalInput10 = false;
	bool DigitalInput11 = false;
	bool DigitalInput12 = false;
	bool DigitalInput13 = false;
	bool DigitalInput14 = false;
	bool DigitalInput15 = false;
	bool DigitalInput16 = false;
	bool DigitalInput17 = false;
	bool DigitalInput18 = false;
	bool DigitalInput19 = false;
	bool DigitalInput20 = false;
	bool DigitalInput21 = false;
	bool DigitalInput22 = false;
	bool DigitalInput23 = false;
	bool DigitalInput24 = false;
	bool DigitalInput25 = false;
	bool DigitalInput26 = false;
	bool DigitalInput27 = false;
	bool DigitalInput28 = false;
	bool DigitalInput29 = false;
	bool DigitalInput30 = false;

	int32 AnalogueInput1 = 0;
	int32 AnalogueInput2 = 0;
	int32 AnalogueInput3 = 0;
	int32 AnalogueInput4 = 0;
	int32 AnalogueInput5 = 0;
	int32 AnalogueInput6 = 0;
	int32 AnalogueInput7 = 0;
	int32 AnalogueInput8 = 0;
	int32 AnalogueInput9 = 0;
	int32 AnalogueInput10 = 0;

	void Reset();
};
