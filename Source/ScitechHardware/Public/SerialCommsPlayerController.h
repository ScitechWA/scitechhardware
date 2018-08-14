

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScitechHardwareInterface.h"
#include "ScitechHardwareDelegate.h"
#include "SerialCommsPlayerController.generated.h"

/**
 *
 */
UCLASS()
class SCITECHHARDWARE_API ASerialCommsPlayerController : public APlayerController, public ScitechHardwareDelegate, public IScitechHardwareInterface
{
	GENERATED_BODY()




public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category = "Serial Comms")
		int ComPort = 3;

	virtual void Tick(float DeltaSeconds) override;


	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
		void SendSerialString(FString outputString);

protected:
	virtual void BeginPlay() override;

};
