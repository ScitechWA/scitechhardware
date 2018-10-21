// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScitechHardwareInterface.h"
#include "SerialCommsState.h"

//Input Mapping Keys
struct EKeysScitechHardware
{
	static const FKey ScitechHardwareDigitalInput1;
	static const FKey ScitechHardwareDigitalInput2;
	static const FKey ScitechHardwareDigitalInput3;
	static const FKey ScitechHardwareDigitalInput4;
	static const FKey ScitechHardwareDigitalInput5;
	static const FKey ScitechHardwareDigitalInput6;
	static const FKey ScitechHardwareDigitalInput7;
	static const FKey ScitechHardwareDigitalInput8;
	static const FKey ScitechHardwareDigitalInput9;
	static const FKey ScitechHardwareDigitalInput10;
	static const FKey ScitechHardwareDigitalInput11;
	static const FKey ScitechHardwareDigitalInput12;
	static const FKey ScitechHardwareDigitalInput13;
	static const FKey ScitechHardwareDigitalInput14;
	static const FKey ScitechHardwareDigitalInput15;
	static const FKey ScitechHardwareDigitalInput16;
	static const FKey ScitechHardwareDigitalInput17;
	static const FKey ScitechHardwareDigitalInput18;
	static const FKey ScitechHardwareDigitalInput19;
	static const FKey ScitechHardwareDigitalInput20;
	static const FKey ScitechHardwareDigitalInput21;
	static const FKey ScitechHardwareDigitalInput22;
	static const FKey ScitechHardwareDigitalInput23;
	static const FKey ScitechHardwareDigitalInput24;
	static const FKey ScitechHardwareDigitalInput25;
	static const FKey ScitechHardwareDigitalInput26;
	static const FKey ScitechHardwareDigitalInput27;
	static const FKey ScitechHardwareDigitalInput28;
	static const FKey ScitechHardwareDigitalInput29;
	static const FKey ScitechHardwareDigitalInput30;

	static const FKey ScitechHardwareAnalogueInput1;
	static const FKey ScitechHardwareAnalogueInput2;
	static const FKey ScitechHardwareAnalogueInput3;
	static const FKey ScitechHardwareAnalogueInput4;
	static const FKey ScitechHardwareAnalogueInput5;
	static const FKey ScitechHardwareAnalogueInput6;
	static const FKey ScitechHardwareAnalogueInput7;
	static const FKey ScitechHardwareAnalogueInput8;
	static const FKey ScitechHardwareAnalogueInput9;
	static const FKey ScitechHardwareAnalogueInput10;

};

/*
struct  ScitechHardwareControllerDataUE{
	//raw converted
	int64 buttonsPressedL;
	int64 buttonsPressedH;
	FVector Axis;
	FVector RAxis;
	FVector POV = FVector(4294967296, 4294967296, 4294967296);
	FVector2D Slider;
	bool enabled;
};
*/

class ScitechHardwareDelegate
{
	friend class FScitechHardware;
public:
	
	virtual void DigitalInputActivated(int32 InputIndex);
	virtual void DigitalInputDeactivated(int32 InputIndex);

	virtual void AnalogueInputChanged(int32 InputIndex, float value);
	
	virtual bool ScitechHardwareIsAvailable();

	//If you want an alternate delegate, set it here
	void SetInterfaceDelegate(UObject* newDelegate);

	//** Required Calls */

	virtual void ScitechHardwareStartup();				//Call this somewhere in an initializing state such as BeginPlay()
	virtual void ScitechHardwareTick(float DeltaTime);	//Call this every tick

	virtual void ScitechHardwareOpenPort(int portNumber);
	virtual void ScitechHardwareClosePort();

	virtual void ScitechHardwareStartReading();
	virtual void ScitechHardwareStopReading();

	virtual void ScitechHardwareStartWriting();
	virtual void ScitechHardwareStopWriting();

	virtual void SendString(FString outputString);
	
	virtual void UpdateStates();
		
protected:
	UObject* ValidSelfPointer;	//REQUIRED: has to be set before HydraStartup by a UObject subclass
	//class UScitechHardwareSingleController* _latestFrame;

	UPROPERTY()
	USerialCommsState* previousState;
	UPROPERTY()
	USerialCommsState* currentState;

private:
	UObject* _interfaceDelegate;
	bool implementsInterface();
};