#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IScitechHardware.h"
#include "SlateBasics.h"

THIRD_PARTY_INCLUDES_START
#include <SerialComms.h>
THIRD_PARTY_INCLUDES_END

//DECLARE_LOG_CATEGORY_EXTERN(ScitechHardware, Log, All);
//DEFINE_LOG_CATEGORY(ScitechHardware);
#define LOCTEXT_NAMESPACE "FScitechHardware"

class FScitechHardware : public IScitechHardware
{
private:
	

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool IsConnected();
	bool OpenPort(int ComPortNumber);
	bool ClosePort();
	bool StartReading();
	bool StopReading();
	bool StartWriting();
	bool StopWriting();
	bool Update();
	bool GetDigitalValue(int ValueIndex);
	bool GetDigitalValueSinceLastUpdate(int ValueIndex);
	int GetAnalogueValue(int ValueIndex);
	void SendString(FString outputString);

	void SetDelegate(ScitechHardwareDelegate* newDelegate);
	void ScitechHardwareTick(float DeltaTime);
protected:
	UPROPERTY()
	SerialPort * comPort;
	UPROPERTY()
	ScitechHardwareDelegate * scitechHardwareDelegate;
private:
	

	void DelegateTick(float DeltaTime);
};



IMPLEMENT_MODULE(FScitechHardware, ScitechHardware)



void FScitechHardware::StartupModule()
{
	comPort = new SerialPort();

	UE_LOG(LogTemp, Log, TEXT("################################### \n"));
	UE_LOG(LogTemp, Log, TEXT("## Starting Scitech Hardware...\n"));
	UE_LOG(LogTemp, Log, TEXT("################################### \n"));

	EKeys::AddMenuCategoryDisplayInfo(TEXT("Scitech Hardware"), LOCTEXT("ScitechHardwareSubCategory", "Scitech Hardware"), TEXT("GraphEditor.Event_16x"));

	// Add each joystick axis.
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput1, LOCTEXT("DigitalValue1", "Digital Value 1"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput2, LOCTEXT("DigitalValue2", "Digital Value 2"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput3, LOCTEXT("DigitalValue3", "Digital Value 3"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput4, LOCTEXT("DigitalValue4", "Digital Value 4"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput5, LOCTEXT("DigitalValue5", "Digital Value 5"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput6, LOCTEXT("DigitalValue6", "Digital Value 6"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput7, LOCTEXT("DigitalValue7", "Digital Value 7"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput8, LOCTEXT("DigitalValue8", "Digital Value 8"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput9, LOCTEXT("DigitalValue9", "Digital Value 9"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput10, LOCTEXT("DigitalValue10", "Digital Value 10"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput11, LOCTEXT("DigitalValue11", "Digital Value 11"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput12, LOCTEXT("DigitalValue12", "Digital Value 12"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput13, LOCTEXT("DigitalValue13", "Digital Value 13"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput14, LOCTEXT("DigitalValue14", "Digital Value 14"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput15, LOCTEXT("DigitalValue15", "Digital Value 15"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput16, LOCTEXT("DigitalValue16", "Digital Value 16"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput17, LOCTEXT("DigitalValue17", "Digital Value 17"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput18, LOCTEXT("DigitalValue18", "Digital Value 18"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput19, LOCTEXT("DigitalValue19", "Digital Value 19"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput20, LOCTEXT("DigitalValue20", "Digital Value 20"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput21, LOCTEXT("DigitalValue21", "Digital Value 21"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput22, LOCTEXT("DigitalValue22", "Digital Value 22"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput23, LOCTEXT("DigitalValue23", "Digital Value 23"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput24, LOCTEXT("DigitalValue24", "Digital Value 24"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput25, LOCTEXT("DigitalValue25", "Digital Value 25"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput26, LOCTEXT("DigitalValue26", "Digital Value 26"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput27, LOCTEXT("DigitalValue27", "Digital Value 27"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput28, LOCTEXT("DigitalValue28", "Digital Value 28"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput29, LOCTEXT("DigitalValue29", "Digital Value 29"), FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareDigitalInput30, LOCTEXT("DigitalValue30", "Digital Value 30"), FKeyDetails::GamepadKey, "Scitech Hardware"));

	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput1, LOCTEXT("AnalogueInput1", "Analogue Input 1"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput2, LOCTEXT("AnalogueInput2", "Analogue Input 2"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput3, LOCTEXT("AnalogueInput3", "Analogue Input 3"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput4, LOCTEXT("AnalogueInput4", "Analogue Input 4"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput5, LOCTEXT("AnalogueInput5", "Analogue Input 5"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput6, LOCTEXT("AnalogueInput6", "Analogue Input 6"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput7, LOCTEXT("AnalogueInput7", "Analogue Input 7"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput8, LOCTEXT("AnalogueInput8", "Analogue Input 8"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput9, LOCTEXT("AnalogueInput9", "Analogue Input 9"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
	EKeys::AddKey(FKeyDetails(EKeysScitechHardware::ScitechHardwareAnalogueInput10, LOCTEXT("AnalogueInput10", "Analogue Input 10"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, "Scitech Hardware"));
}


void FScitechHardware::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("################################### \n"));
	UE_LOG(LogTemp, Log, TEXT("## Stopping Scitech Hardware... \n"));
	UE_LOG(LogTemp, Log, TEXT("################################### \n"));

	if (comPort != NULL)
	{
		if (comPort->isConnected())
		{
			comPort->closeSerialPort();
		}
	}
}

bool FScitechHardware::IsConnected()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->isConnected();
		}
		else
		{
			return 0;
		}
	}
	else return 0;
}

bool FScitechHardware::OpenPort(int ComPortNumber)
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->openSerialPort(ComPortNumber);
		}
		return false;
	}
	return false;
}

bool FScitechHardware::ClosePort()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->closeSerialPort();
		}
		return false;
	}
	return false;
}

bool FScitechHardware::StartReading()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			comPort->startReading();
			return true;
		}
		return false;
	}
	return false;
}

bool FScitechHardware::StopReading()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			comPort->stopReading();
			return true;
		}
		return false;
	}
	return false;
}

bool FScitechHardware::StartWriting()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			comPort->startWriting();
			return true;
		}
		return false;
	}
	return false;
}

bool FScitechHardware::StopWriting()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			comPort->stopWriting();
			return true;
		}
		return false;
	}
	return false;
}

bool FScitechHardware::Update()
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->update();
		}
		return false;
	}
	return false;
}

bool FScitechHardware::GetDigitalValue(int ValueIndex)
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->getDigitalValue(ValueIndex);
		}
		return false;
	}
	return false;
}

bool FScitechHardware::GetDigitalValueSinceLastUpdate(int ValueIndex)
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->getDigitalValue(ValueIndex, true);
		}
		return false;
	}
	return false;
}

int FScitechHardware::GetAnalogueValue(int ValueIndex)
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->getAnalogueValue(ValueIndex);
		}
		return false;
	}
	return false;
}

void FScitechHardware::SendString(FString outputString)
{
	if (IsAvailable())
	{
		if (comPort != NULL)
		{
			return comPort->sendCharacters(TCHAR_TO_ANSI(*outputString));
		}
	}
}

void FScitechHardware::SetDelegate(ScitechHardwareDelegate* newDelegate)
{
	scitechHardwareDelegate = newDelegate;
}

void FScitechHardware::ScitechHardwareTick(float DeltaTime)
{
	if (scitechHardwareDelegate != NULL)
	{
		DelegateTick(DeltaTime);
	}
}

bool EmitHardwareKeyUpEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool EmitHardwareKeyDownEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool EmitHardwareAnalogInputEventForKey(FKey key, float value, int32 user, bool repeat)
{
	FAnalogInputEvent AnalogInputEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0, value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}

void FScitechHardware::DelegateTick(float DeltaTime)
{
	if (scitechHardwareDelegate == NULL) return;

	scitechHardwareDelegate->UpdateStates();

	// Digital Down Events
	if (!IsValid(scitechHardwareDelegate->currentState))
	{
		UE_LOG(LogTemp, Log, TEXT("FScitechHardware::DelegateTick() currentState Invalid\n"));
		return;
	}
	if (!IsValid(scitechHardwareDelegate->previousState))
	{
		UE_LOG(LogTemp, Log, TEXT("FScitechHardware::DelegateTick() previousState Invalid\n"));
		return;
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput1) && (!scitechHardwareDelegate->previousState->DigitalInput1))
	{
		scitechHardwareDelegate->DigitalInputActivated(1);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput1, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput2) && (!scitechHardwareDelegate->previousState->DigitalInput2))
	{
		scitechHardwareDelegate->DigitalInputActivated(2);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput2, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput3) && (!scitechHardwareDelegate->previousState->DigitalInput3))
	{
		scitechHardwareDelegate->DigitalInputActivated(3);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput3, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput4) && (!scitechHardwareDelegate->previousState->DigitalInput4))
	{
		scitechHardwareDelegate->DigitalInputActivated(4);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput4, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput5) && (!scitechHardwareDelegate->previousState->DigitalInput5))
	{
		scitechHardwareDelegate->DigitalInputActivated(5);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput5, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput6) && (!scitechHardwareDelegate->previousState->DigitalInput6))
	{
		scitechHardwareDelegate->DigitalInputActivated(6);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput6, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput7) && (!scitechHardwareDelegate->previousState->DigitalInput7))
	{
		scitechHardwareDelegate->DigitalInputActivated(7);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput7, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput8) && (!scitechHardwareDelegate->previousState->DigitalInput8))
	{
		scitechHardwareDelegate->DigitalInputActivated(8);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput8, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput9) && (!scitechHardwareDelegate->previousState->DigitalInput9))
	{
		scitechHardwareDelegate->DigitalInputActivated(9);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput9, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput10) && (!scitechHardwareDelegate->previousState->DigitalInput10))
	{
		scitechHardwareDelegate->DigitalInputActivated(10);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput10, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput11) && (!scitechHardwareDelegate->previousState->DigitalInput11))
	{
		scitechHardwareDelegate->DigitalInputActivated(11);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput11, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput12) && (!scitechHardwareDelegate->previousState->DigitalInput12))
	{
		scitechHardwareDelegate->DigitalInputActivated(12);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput12, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput13) && (!scitechHardwareDelegate->previousState->DigitalInput13))
	{
		scitechHardwareDelegate->DigitalInputActivated(13);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput13, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput14) && (!scitechHardwareDelegate->previousState->DigitalInput14))
	{
		scitechHardwareDelegate->DigitalInputActivated(14);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput14, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput15) && (!scitechHardwareDelegate->previousState->DigitalInput15))
	{
		scitechHardwareDelegate->DigitalInputActivated(15);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput15, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput16) && (!scitechHardwareDelegate->previousState->DigitalInput16))
	{
		scitechHardwareDelegate->DigitalInputActivated(16);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput16, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput17) && (!scitechHardwareDelegate->previousState->DigitalInput17))
	{
		scitechHardwareDelegate->DigitalInputActivated(17);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput17, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput18) && (!scitechHardwareDelegate->previousState->DigitalInput18))
	{
		scitechHardwareDelegate->DigitalInputActivated(18);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput18, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput19) && (!scitechHardwareDelegate->previousState->DigitalInput19))
	{
		scitechHardwareDelegate->DigitalInputActivated(19);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput19, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput20) && (!scitechHardwareDelegate->previousState->DigitalInput20))
	{
		scitechHardwareDelegate->DigitalInputActivated(20);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput20, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput21) && (!scitechHardwareDelegate->previousState->DigitalInput21))
	{
		scitechHardwareDelegate->DigitalInputActivated(21);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput21, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput22) && (!scitechHardwareDelegate->previousState->DigitalInput22))
	{
		scitechHardwareDelegate->DigitalInputActivated(22);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput22, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput23) && (!scitechHardwareDelegate->previousState->DigitalInput23))
	{
		scitechHardwareDelegate->DigitalInputActivated(23);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput23, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput24) && (!scitechHardwareDelegate->previousState->DigitalInput24))
	{
		scitechHardwareDelegate->DigitalInputActivated(24);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput24, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput25) && (!scitechHardwareDelegate->previousState->DigitalInput25))
	{
		scitechHardwareDelegate->DigitalInputActivated(25);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput25, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput26) && (!scitechHardwareDelegate->previousState->DigitalInput26))
	{
		scitechHardwareDelegate->DigitalInputActivated(26);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput26, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput27) && (!scitechHardwareDelegate->previousState->DigitalInput27))
	{
		scitechHardwareDelegate->DigitalInputActivated(27);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput27, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput28) && (!scitechHardwareDelegate->previousState->DigitalInput28))
	{
		scitechHardwareDelegate->DigitalInputActivated(28);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput28, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput29) && (!scitechHardwareDelegate->previousState->DigitalInput29))
	{
		scitechHardwareDelegate->DigitalInputActivated(29);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput29, 0, 0);
	}
	if ((scitechHardwareDelegate->currentState->DigitalInput30) && (!scitechHardwareDelegate->previousState->DigitalInput30))
	{
		scitechHardwareDelegate->DigitalInputActivated(30);
		EmitHardwareKeyDownEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput30, 0, 0);
	}

	// Digital Up Events
	if ((scitechHardwareDelegate->previousState->DigitalInput1) && (!scitechHardwareDelegate->currentState->DigitalInput1))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 1 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(1);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput1, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput2) && (!scitechHardwareDelegate->currentState->DigitalInput2))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 2 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(2);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput2, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput3) && (!scitechHardwareDelegate->currentState->DigitalInput3))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 3 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(3);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput3, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput4) && (!scitechHardwareDelegate->currentState->DigitalInput4))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 4 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(4);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput4, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput5) && (!scitechHardwareDelegate->currentState->DigitalInput5))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 5 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(5);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput5, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput6) && (!scitechHardwareDelegate->currentState->DigitalInput6))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 6 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(6);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput6, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput7) && (!scitechHardwareDelegate->currentState->DigitalInput7))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 7 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(7);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput7, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput8) && (!scitechHardwareDelegate->currentState->DigitalInput8))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 8 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(8);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput8, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput9) && (!scitechHardwareDelegate->currentState->DigitalInput9))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 9 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(9);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput9, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput10) && (!scitechHardwareDelegate->currentState->DigitalInput10))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 10 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(10);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput10, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput11) && (!scitechHardwareDelegate->currentState->DigitalInput11))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 11 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(11);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput11, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput12) && (!scitechHardwareDelegate->currentState->DigitalInput12))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 12 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(12);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput12, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput13) && (!scitechHardwareDelegate->currentState->DigitalInput13))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 13 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(13);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput13, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput14) && (!scitechHardwareDelegate->currentState->DigitalInput14))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 14 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(14);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput14, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput15) && (!scitechHardwareDelegate->currentState->DigitalInput15))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 15 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(15);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput15, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput16) && (!scitechHardwareDelegate->currentState->DigitalInput16))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 16 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(16);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput16, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput17) && (!scitechHardwareDelegate->currentState->DigitalInput17))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 17 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(17);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput17, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput18) && (!scitechHardwareDelegate->currentState->DigitalInput18))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 18 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(18);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput18, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput19) && (!scitechHardwareDelegate->currentState->DigitalInput19))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 19 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(19);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput19, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput20) && (!scitechHardwareDelegate->currentState->DigitalInput20))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 20 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(20);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput20, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput21) && (!scitechHardwareDelegate->currentState->DigitalInput21))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 21 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(21);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput21, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput22) && (!scitechHardwareDelegate->currentState->DigitalInput22))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 22 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(22);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput22, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput23) && (!scitechHardwareDelegate->currentState->DigitalInput23))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 23 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(23);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput23, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput24) && (!scitechHardwareDelegate->currentState->DigitalInput24))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 24 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(24);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput24, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput25) && (!scitechHardwareDelegate->currentState->DigitalInput25))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 25 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(25);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput25, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput26) && (!scitechHardwareDelegate->currentState->DigitalInput26))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 26 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(26);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput26, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput27) && (!scitechHardwareDelegate->currentState->DigitalInput27))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 27 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(27);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput27, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput28) && (!scitechHardwareDelegate->currentState->DigitalInput28))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 28 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(28);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput28, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput29) && (!scitechHardwareDelegate->currentState->DigitalInput29))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 29 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(29);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput29, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->DigitalInput30) && (!scitechHardwareDelegate->currentState->DigitalInput30))
	{
		UE_LOG(LogTemp, Log, TEXT("Digital Input 30 Deactivating...\n"));
		scitechHardwareDelegate->DigitalInputDeactivated(30);
		EmitHardwareKeyUpEventForKey(EKeysScitechHardware::ScitechHardwareDigitalInput30, 0, 0);
	}

	// ANALOGUE EVENTS
	if ((scitechHardwareDelegate->previousState->AnalogueInput1) != (scitechHardwareDelegate->currentState->AnalogueInput1))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput1) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(1, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput1, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput2) != (scitechHardwareDelegate->currentState->AnalogueInput2))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput2) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput2, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput3) != (scitechHardwareDelegate->currentState->AnalogueInput3))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput3) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput3, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput4) != (scitechHardwareDelegate->currentState->AnalogueInput4))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput4) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput4, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput5) != (scitechHardwareDelegate->currentState->AnalogueInput5))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput5) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput5, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput6) != (scitechHardwareDelegate->currentState->AnalogueInput6))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput6) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput6, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput7) != (scitechHardwareDelegate->currentState->AnalogueInput7))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput7) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput7, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput8) != (scitechHardwareDelegate->currentState->AnalogueInput8))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput8) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput8, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput9) != (scitechHardwareDelegate->currentState->AnalogueInput9))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput9) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput9, value, 0, 0);
	}
	if ((scitechHardwareDelegate->previousState->AnalogueInput10) != (scitechHardwareDelegate->currentState->AnalogueInput10))
	{
		float value = (float)(scitechHardwareDelegate->currentState->AnalogueInput10) / 1000.0f;
		scitechHardwareDelegate->AnalogueInputChanged(2, value);
		EmitHardwareAnalogInputEventForKey(EKeysScitechHardware::ScitechHardwareAnalogueInput10, value, 0, 0);
	}
	Update();
}

