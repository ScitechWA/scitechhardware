

#pragma once

#include "CoreMinimal.h"
#include "ScitechHardwareDelegate.h"
#include "Components/ActorComponent.h"
#include "ScitechHardwareComponent.generated.h"


UCLASS( ClassGroup="Serial Comms", meta=(BlueprintSpawnableComponent) )
class SCITECHHARDWARE_API UScitechHardwareComponent : public UActorComponent, public ScitechHardwareDelegate
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScitechHardwareComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Serial Comms")
		int ComPort = 3;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Town Map Comms")
		bool IsAvailable();


	virtual void OnRegister() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
