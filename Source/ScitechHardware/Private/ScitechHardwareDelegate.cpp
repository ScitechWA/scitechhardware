// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

//#include "ScitechHardwarePluginPrivatePCH.h"
#include "CoreMinimal.h"
#include "ScitechHardwareDelegate.h"
#include "IScitechHardware.h"
#include "InputCoreTypes.h"

const FKey EKeysScitechHardware::ScitechHardwareDigitalInput1("ScitechHardwareDigitalInput1");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput2("ScitechHardwareDigitalInput2");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput3("ScitechHardwareDigitalInput3");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput4("ScitechHardwareDigitalInput4");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput5("ScitechHardwareDigitalInput5");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput6("ScitechHardwareDigitalInput6");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput7("ScitechHardwareDigitalInput7");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput8("ScitechHardwareDigitalInput8");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput9("ScitechHardwareDigitalInput9");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput10("ScitechHardwareDigitalInput10");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput11("ScitechHardwareDigitalInput11");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput12("ScitechHardwareDigitalInput12");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput13("ScitechHardwareDigitalInput13");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput14("ScitechHardwareDigitalInput14");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput15("ScitechHardwareDigitalInput15");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput16("ScitechHardwareDigitalInput16");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput17("ScitechHardwareDigitalInput17");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput18("ScitechHardwareDigitalInput18");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput19("ScitechHardwareDigitalInput19");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput20("ScitechHardwareDigitalInput20");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput21("ScitechHardwareDigitalInput21");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput22("ScitechHardwareDigitalInput22");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput23("ScitechHardwareDigitalInput23");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput24("ScitechHardwareDigitalInput24");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput25("ScitechHardwareDigitalInput25");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput26("ScitechHardwareDigitalInput26");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput27("ScitechHardwareDigitalInput27");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput28("ScitechHardwareDigitalInput28");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput29("ScitechHardwareDigitalInput29");
const FKey EKeysScitechHardware::ScitechHardwareDigitalInput30("ScitechHardwareDigitalInput30");

const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput1("ScitechHardwareAnalogueInput1");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput2("ScitechHardwareAnalogueInput2");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput3("ScitechHardwareAnalogueInput3");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput4("ScitechHardwareAnalogueInput4");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput5("ScitechHardwareAnalogueInput5");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput6("ScitechHardwareAnalogueInput6");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput7("ScitechHardwareAnalogueInput7");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput8("ScitechHardwareAnalogueInput8");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput9("ScitechHardwareAnalogueInput9");
const FKey EKeysScitechHardware::ScitechHardwareAnalogueInput10("ScitechHardwareAnalogueInput10");

// Empty Event Functions, no Super call required, because they don't do anything!
void ScitechHardwareDelegate::DigitalInputActivated(int32 buttonNr)
{
	if (implementsInterface())
		IScitechHardwareInterface::Execute_DigitalInputActivated(_interfaceDelegate, buttonNr);
}

void ScitechHardwareDelegate::DigitalInputDeactivated(int32 buttonNr)
{
	if (implementsInterface())
		IScitechHardwareInterface::Execute_DigitalInputDeactivated(_interfaceDelegate, buttonNr);
}

void ScitechHardwareDelegate::AnalogueInputChanged(int32 inputNr, float value)
{
	if (implementsInterface())
		IScitechHardwareInterface::Execute_AnalogueInputChanged(_interfaceDelegate, inputNr, value);
}



bool ScitechHardwareDelegate::implementsInterface()
{
	return (_interfaceDelegate != NULL && _interfaceDelegate->GetClass()->ImplementsInterface(UScitechHardwareInterface::StaticClass()));
}

//Setting
void ScitechHardwareDelegate::SetInterfaceDelegate(UObject* newDelegate)
{
	//UE_LOG(ScitechHardwarePluginLog, Log, TEXT("InterfaceDelegate passed: %s"), *newDelegate->GetName());

	//Use this format to support both blueprint and C++ form
	if (newDelegate->GetClass()->ImplementsInterface(UScitechHardwareInterface::StaticClass()))
	{
		_interfaceDelegate = newDelegate;
	}
	else
	{
		//Try casting as self
		if (ValidSelfPointer->GetClass()->ImplementsInterface(UScitechHardwareInterface::StaticClass()))
		{
			_interfaceDelegate = (UObject*)this;
		}
		else
		{
			//If you're crashing its probably because of this setting causing an assert failure
			_interfaceDelegate = NULL;
			//UE_LOG(ScitechHardwarePluginLog, Log, TEXT("ScitechHardwareBlueprintDelegate Warning: ScitechHardwareInterface delegate is NULL, did your class implement ScitechHardwareInterface? Events are disabled."));
		}

		//Either way post a warning, this will be a common error
		//UE_LOG(ScitechHardwarePluginLog, Log, TEXT("ScitechHardwareBlueprintDelegate Warning: ScitechHardwareInterface Delegate is NOT set, did your class implement ScitechHardwareInterface? Events are disabled."));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ScitechHardwareBlueprintDelegate Warning: Delegate is NOT set, did your class implement ScitechHardwareInterface? Events are disabled."));
	}
}

//Startup
void ScitechHardwareDelegate::ScitechHardwareStartup()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - Set self as a delegate
		IScitechHardware::Get().SetDelegate((ScitechHardwareDelegate*)this);
	}

	UObject* validUObject = NULL;
	validUObject = Cast<UObject>(ValidSelfPointer);

	//Set self as interface delegate by default
	if (!_interfaceDelegate && validUObject)
		SetInterfaceDelegate(validUObject);

	previousState = NewObject<USerialCommsState>();
	currentState = NewObject<USerialCommsState>();
}

/*
UScitechHardwareSingleController* ScitechHardwareDelegate::ScitechHardwareGetLatestFrame()
{
	return _latestFrame;
}
*/
bool ScitechHardwareDelegate::ScitechHardwareIsAvailable()
{
	return true;
}

void ScitechHardwareDelegate::ScitechHardwareTick(float DeltaTime)
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().ScitechHardwareTick(DeltaTime);
	}
}


void ScitechHardwareDelegate::ScitechHardwareOpenPort(int portNumber)
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().OpenPort(portNumber);
	}
}

void ScitechHardwareDelegate::ScitechHardwareClosePort()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().ClosePort();
	}
}

void ScitechHardwareDelegate::ScitechHardwareStartReading()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().StartReading();
	}
}

void ScitechHardwareDelegate::ScitechHardwareStopReading()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().StopReading();
	}
}

void ScitechHardwareDelegate::ScitechHardwareStartWriting()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().StartWriting();
	}
}

void ScitechHardwareDelegate::ScitechHardwareStopWriting()
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().StopWriting();
	}
}

void ScitechHardwareDelegate::SendString(FString outputString)
{
	if (IScitechHardware::IsAvailable())
	{
		//Required to Work - This is the plugin magic
		IScitechHardware::Get().SendString(outputString);
	}
}

void ScitechHardwareDelegate::UpdateStates()
{
	//currentState->DigitalInput1 
	if (IScitechHardware::IsAvailable())
	{
		previousState->DigitalInput1 = currentState->DigitalInput1;
		previousState->DigitalInput2 = currentState->DigitalInput2;
		previousState->DigitalInput3 = currentState->DigitalInput3;
		previousState->DigitalInput4 = currentState->DigitalInput4;
		previousState->DigitalInput5 = currentState->DigitalInput5;
		previousState->DigitalInput6 = currentState->DigitalInput6;
		previousState->DigitalInput7 = currentState->DigitalInput7;
		previousState->DigitalInput8 = currentState->DigitalInput8;
		previousState->DigitalInput9 = currentState->DigitalInput9;
		previousState->DigitalInput10 = currentState->DigitalInput10;
		previousState->DigitalInput11 = currentState->DigitalInput11;
		previousState->DigitalInput12 = currentState->DigitalInput12;
		previousState->DigitalInput13 = currentState->DigitalInput13;
		previousState->DigitalInput14 = currentState->DigitalInput14;
		previousState->DigitalInput15 = currentState->DigitalInput15;
		previousState->DigitalInput16 = currentState->DigitalInput16;
		previousState->DigitalInput17 = currentState->DigitalInput17;
		previousState->DigitalInput18 = currentState->DigitalInput18;
		previousState->DigitalInput19 = currentState->DigitalInput19;
		previousState->DigitalInput20 = currentState->DigitalInput20;
		previousState->DigitalInput21 = currentState->DigitalInput21;
		previousState->DigitalInput22 = currentState->DigitalInput22;
		previousState->DigitalInput23 = currentState->DigitalInput23;
		previousState->DigitalInput24 = currentState->DigitalInput24;
		previousState->DigitalInput25 = currentState->DigitalInput25;
		previousState->DigitalInput26 = currentState->DigitalInput26;
		previousState->DigitalInput27 = currentState->DigitalInput27;
		previousState->DigitalInput28 = currentState->DigitalInput28;
		previousState->DigitalInput29 = currentState->DigitalInput29;
		previousState->DigitalInput30 = currentState->DigitalInput30;
		
		previousState->AnalogueInput1 = currentState->AnalogueInput1;
		previousState->AnalogueInput2 = currentState->AnalogueInput2;
		previousState->AnalogueInput3 = currentState->AnalogueInput3;
		previousState->AnalogueInput4 = currentState->AnalogueInput4;
		previousState->AnalogueInput5 = currentState->AnalogueInput5;
		previousState->AnalogueInput6 = currentState->AnalogueInput6;
		previousState->AnalogueInput7 = currentState->AnalogueInput7;
		previousState->AnalogueInput8 = currentState->AnalogueInput8;
		previousState->AnalogueInput9 = currentState->AnalogueInput9;
		previousState->AnalogueInput10 = currentState->AnalogueInput10;

		currentState->DigitalInput1 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(1);
		currentState->DigitalInput2 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(2);
		currentState->DigitalInput3 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(3);
		currentState->DigitalInput4 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(4);
		currentState->DigitalInput5 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(5);
		currentState->DigitalInput6 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(6);
		currentState->DigitalInput7 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(7);
		currentState->DigitalInput8 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(8);
		currentState->DigitalInput9 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(9);
		currentState->DigitalInput10 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(10);
		currentState->DigitalInput11 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(11);
		currentState->DigitalInput12 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(12);
		currentState->DigitalInput13 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(13);
		currentState->DigitalInput14 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(14);
		currentState->DigitalInput15 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(15);
		currentState->DigitalInput16 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(16);
		currentState->DigitalInput17 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(17);
		currentState->DigitalInput18 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(18);
		currentState->DigitalInput19 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(19);
		currentState->DigitalInput20 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(20);
		currentState->DigitalInput21 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(21);
		currentState->DigitalInput22 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(22);
		currentState->DigitalInput23 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(23);
		currentState->DigitalInput24 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(24);
		currentState->DigitalInput25 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(25);
		currentState->DigitalInput26 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(26);
		currentState->DigitalInput27 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(27);
		currentState->DigitalInput28 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(28);
		currentState->DigitalInput29 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(29);
		currentState->DigitalInput30 = IScitechHardware::Get().GetDigitalValueSinceLastUpdate(30);

		currentState->AnalogueInput1 = IScitechHardware::Get().GetAnalogueValue(1);
		currentState->AnalogueInput2 = IScitechHardware::Get().GetAnalogueValue(2);
		currentState->AnalogueInput3 = IScitechHardware::Get().GetAnalogueValue(3);
		currentState->AnalogueInput4 = IScitechHardware::Get().GetAnalogueValue(4);
		currentState->AnalogueInput5 = IScitechHardware::Get().GetAnalogueValue(5);
		currentState->AnalogueInput6 = IScitechHardware::Get().GetAnalogueValue(6);
		currentState->AnalogueInput7 = IScitechHardware::Get().GetAnalogueValue(7);
		currentState->AnalogueInput8 = IScitechHardware::Get().GetAnalogueValue(8);
		currentState->AnalogueInput9 = IScitechHardware::Get().GetAnalogueValue(9);
		currentState->AnalogueInput10 = IScitechHardware::Get().GetAnalogueValue(10);
	}
}
