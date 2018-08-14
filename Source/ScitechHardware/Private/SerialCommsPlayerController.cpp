
#include "CoreMinimal.h"
#include "SerialCommsPlayerController.h"




void ASerialCommsPlayerController::Tick(float DeltaSeconds)
{
	APlayerController::Tick(DeltaSeconds);
	ScitechHardwareTick(DeltaSeconds);
}

void ASerialCommsPlayerController::Destroyed()
{
	Super::Destroyed();

	ScitechHardwareStopWriting();
	ScitechHardwareStopReading();
	ScitechHardwareClosePort();
}

void ASerialCommsPlayerController::SendSerialString(FString outputString)
{
	SendString(outputString);
}

void ASerialCommsPlayerController::BeginPlay()
{
	APlayerController::BeginPlay();
	ValidSelfPointer = this;
	ScitechHardwareStartup();

	ScitechHardwareOpenPort(ComPort);
	ScitechHardwareStartReading();
	ScitechHardwareStartWriting();
}


